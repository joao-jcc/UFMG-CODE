module flip_flop_d(D, CLK, Q);

output reg Q;
input D, CLK;

always @(posedge CLK) 
begin
    Q = D;
end


endmodule
