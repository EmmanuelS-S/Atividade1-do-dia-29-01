// Inclusão de bibliotecas necessárias
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/gpio.h"

// Define os pinos dos LEDs
#define LED_RED_PIN 11
#define LED_YELLOW_PIN 12
#define LED_GREEN_PIN 13

// Variáveis globais
volatile int current_light = 0; // 0 = vermelho, 1 = amarelo, 2 = verde

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

int main() {
    // Inicialização do hardware
    stdio_init_all();
    gpio_init(LED_RED_PIN);
    gpio_init(LED_YELLOW_PIN);
    gpio_init(LED_GREEN_PIN);

    gpio_set_dir(LED_RED_PIN, GPIO_OUT);
    gpio_set_dir(LED_YELLOW_PIN, GPIO_OUT);
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);

    // Configuração do temporizador periódico
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Loop principal
    while (true) {
        // Mensagem na porta serial
        printf("LED ativo: %d\n", current_light);
        sleep_ms(1000);
    }
}
