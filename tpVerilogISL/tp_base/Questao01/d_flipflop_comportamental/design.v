module Dflipflop (clk, reset, D, Q1, Q2);
  input clk;
  input reset;  
  input D;
  output Q1;     
  output Q2;     

  reg Q1;        // Registrador Q1

  assign Q2 = ~Q1;  // Atribuição complementar de Q1 para Q2

  always @(posedge clk or posedge reset)
  begin
    case(reset)    // Caso o sinal de reset
      1'b0 : Q1 = 1;     // Reset ativo: Q1 é atribuído como 1
      1'b1 : Q1 = 0;     // Reset inativo: Q1 é atribuído como 0
      default : Q1 = 0;  // Valor padrão para outros casos
    endcase
  end
endmodule