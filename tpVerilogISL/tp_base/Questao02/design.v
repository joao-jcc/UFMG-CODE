module reg_streamcipher (
  input clk,
  input reset,
  input S1,
  input S2,
  input [7:0] entrada, // Entrada de 8 bits
  output reg saida_e,
  output reg saida_d,
  output reg [7:0] saida // Saida de 8 bits
);

  // Parâmetros locais para auxiliar a visualização
  localparam BIT_MAX = 7, BIT_MIN = 0, REG_MAX = 8'b11111111;

  wire entrada_e;
  wire entrada_d;

  assign entrada_e = (saida[BIT_MIN] ^ saida[BIT_MIN + 1]);
  assign entrada_d = (saida[BIT_MAX] ^ saida[BIT_MAX - 1]);

  always @(posedge clk) begin
    // Se o sinal de reset estiver ativo
    if (reset) begin 
      saida <= REG_MAX;
      saida_e <= 1'b0;
      saida_d <= 1'b0;
    end

    // Se ambos os sinais de controle S1 e S2 estiverem ativos
    else if (S1 && S2) begin
      saida_e <= entrada[BIT_MAX];
      saida_d <= entrada[BIT_MIN];
      saida <= entrada;
    end

    // Se apenas o sinal de controle S1 estiver ativo e S2 estiver inativo
    else if (S1 && !S2) begin
      saida_e <= saida[BIT_MAX];
      saida <= {saida[BIT_MAX - 1:BIT_MIN], entrada_d};
    end

    // Se apenas o sinal de controle S2 estiver ativo e S1 estiver inativo
    else if (!S1 && S2) begin
      saida_d <= saida[BIT_MIN];
      saida <= {entrada_e, saida[BIT_MAX:BIT_MIN + 1]};
    end
  end

endmodule