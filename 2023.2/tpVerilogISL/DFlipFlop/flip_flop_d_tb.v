`timescale 1ns/1ns
`include "flip_flop_d.v"

module flip_flop_d_tb;

reg D = 0, CLK = 0;
wire Q;

flip_flop_d ffd(D, CLK, Q);

always begin
    CLK = ~CLK;
    #10;
end

initial begin
    $dumpfile("flip_flop_d.vcd");
    $dumpvars(0, flip_flop_d_tb);

    repeat (5) begin

        D = ~D;
        #25;

    end

    $finish;
end

endmodule
