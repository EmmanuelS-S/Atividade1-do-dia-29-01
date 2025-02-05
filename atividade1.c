// Inclusão de bibliotecas necessárias
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/gpio.h"

// Define os pinos dos LEDs e do botão
#define LED_RED_PIN 11
#define LED_YELLOW_PIN 12
#define LED_GREEN_PIN 13
#define BUTTON_PIN 5

// Variáveis globais
volatile int current_light = 0; // 0 = vermelho, 1 = amarelo, 2 = verde
volatile bool button_pressed = false;

// Função de callback para o temporizador periódico
bool repeating_timer_callback(struct repeating_timer *t) {
    // Alterna entre os LEDs
    gpio_put(LED_RED_PIN, current_light == 0);
    gpio_put(LED_YELLOW_PIN, current_light == 1);
    gpio_put(LED_GREEN_PIN, current_light == 2);

    // Atualiza o estado do semáforo
    current_light = (current_light + 1) % 3;

    return true; // Mantém o temporizador repetindo
}

// Função de callback para o botão (One-Shot)
bool button_callback(struct repeating_timer *t) {
    static int state = 0;

    if (state == 0) {
        gpio_put(LED_RED_PIN, true);
        gpio_put(LED_YELLOW_PIN, true);
        gpio_put(LED_GREEN_PIN, true);
        state = 1;
    } else if (state == 1) {
        gpio_put(LED_GREEN_PIN, false);
        state = 2;
    } else if (state == 2) {
        gpio_put(LED_YELLOW_PIN, false);
        state = 3;
    } else if (state == 3) {
        gpio_put(LED_RED_PIN, false);
        state = 0;
    }

    return false; // Não repete
}

// Função de debounce para o botão
void debounce_button() {
    static absolute_time_t last_press = {0};
    absolute_time_t now = get_absolute_time();

    if (absolute_time_diff_us(last_press, now) > 3000000) { // 3 segundos
        button_pressed = true;
        last_press = now;
    }
}

int main() {
    // Inicialização do hardware
    stdio_init_all();
    gpio_init(LED_RED_PIN);
    gpio_init(LED_YELLOW_PIN);
    gpio_init(LED_GREEN_PIN);
    gpio_init(BUTTON_PIN);

    gpio_set_dir(LED_RED_PIN, GPIO_OUT);
    gpio_set_dir(LED_YELLOW_PIN, GPIO_OUT);
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    // Configuração do temporizador periódico
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Loop principal
    while (true) {
        // Verifica o estado do botão
        if (!gpio_get(BUTTON_PIN)) {
            debounce_button();
        }

        if (button_pressed) {
            button_pressed = false;
            add_alarm_in_ms(3000, button_callback, NULL, true);
        }

        // Mensagem na porta serial
        printf("LED ativo: %d\n", current_light);
        sleep_ms(1000);
    }
}
