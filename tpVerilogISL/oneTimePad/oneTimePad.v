module oneTimePad #(
  parameter N = 8, // Tamanho padrão da chave
  parameter M = 8  // Tamanho padrão do texto
)(
  input wire [M-1:0] plaintext,
  input wire [N-1:0] key,
  output wire [M-1:0] ciphertext,
  output wire [M-1:0] decryptedtext
);

  // Replicar a chave para que ela tenha o mesmo tamanho que o texto
  wire [M-1:0] expanded_key;
  genvar i;
  generate
    for (i = 0; i < M; i=i+1) begin : key_replication
      assign expanded_key[i] = key[i % N]; // Repetir a chave conforme necessário
    end
  endgenerate

  // XOR operation for encryption
  assign ciphertext = plaintext ^ expanded_key;
  
  // XOR operation for decryption
  assign decryptedtext = ciphertext ^ expanded_key;

endmodule
