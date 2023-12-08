module half_adder(sum, carry, a, b);
    output sum, carry;
    input a, b;

    xor xor1(sum, a, b);
    and and1(carry, a, b);

endmodule