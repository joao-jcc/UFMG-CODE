module Dflipflop (clk, reset, D, Q);
  input wire clk;
  input wire reset;
  input wire D;
  output Q;

  reg Q;

  always @(posedge clk) begin
    if (reset) begin
      Q <= 1'b0; // Reseta a saída para 0
    end else begin
      Q <= D; // Atribui o valor de entrada D à saída Q
    end
  end

endmodule