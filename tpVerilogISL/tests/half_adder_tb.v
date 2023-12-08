/* testbench for half_adder.v saved in file half_adder_tb.v */

`include "half_adder.v"

module half_adder_tb;
    reg a, b;
    wire sum, carry;

    half_adder add1(.sum(sum), .carry(carry), .a(a), .b(b));

    initial 
        begin
            $dumpfile("half_adder.vcd");
            $dumpvars(0, half_adder_tb);

            // Use initial blocks for assigning values
            a = 0; b = 0; #1;
            a = 0; b = 1; #1;
            a = 1; b = 0; #1;
            a = 1; b = 1; #1;

        end

endmodule