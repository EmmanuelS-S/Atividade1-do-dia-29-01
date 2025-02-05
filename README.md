### Instruções Resumidas para Uso do Código

1. **Objetivo**:
   - Implementar um sistema com duas funcionalidades:
     - Um semáforo periódico que alterna entre os LEDs vermelho, amarelo e verde a cada 3 segundos.
     - Um sistema de "one-shot" acionado por um botão que ativa todos os LEDs e os desliga em sequência.

---

2. **Lógica**:

  -Um temporizador periódico (repeating_timer) é configurado para executar a cada 3 segundos.
  -A função repeating_timer_callback alterna o estado dos LEDs, acendendo um LED por vez em sequência (vermelho → amarelo → verde → vermelho...).

---

3. **Como Funciona**:
   - Semáforo Periódico:
     - A cada 3 segundos, o LED ativo muda de vermelho → amarelo → verde, e assim por diante.
   - **Acionamento por Botão:
     - Quando o botão é pressionado:
       1. Todos os LEDs são acesos.
       2. Após 3 segundos, os LEDs são desligados sequencialmente:
          - Verde → Amarelo → Vermelho.

---

4. **Conclusão**
  -O programa simula o funcionamento de um semáforo simples, alternando os LEDs automaticamente a cada 3 segundos sem necessidade de interação externa.   
