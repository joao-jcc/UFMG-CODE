`include "oneTimePad.v"

module oneTimePadTb;

  // Parâmetros para o tamanho da chave e do texto
  parameter N = 2;
  parameter M = 6;

  // Sinais de entrada e saída
  reg [M-1:0] plaintext;
  reg [N-1:0] key;
  wire [M-1:0] ciphertext;
  wire [M-1:0] decryptedtext;

  // Instanciar o módulo oneTimePad
  oneTimePad #(
    .N(N),
    .M(M)
  ) uut (
    .plaintext(plaintext),
    .key(key),
    .ciphertext(ciphertext),
    .decryptedtext(decryptedtext)
  );

  // Testbench
  initial begin
    // Inicializar valores
    plaintext = 6'b101010; 
    key = 2'b01; 

    // Exibir valores iniciais
    $display("Plaintext:    %b", plaintext);
    $display("Key:          %b", key);

    // Simular a codificação e decodificação
    #1; // Aguardar um ciclo
    $display("Ciphertext:   %b", ciphertext);
    $display("Decryptedtext:%b", decryptedtext);

    // Finalizar a simulação
    $finish;
  end

endmodule
