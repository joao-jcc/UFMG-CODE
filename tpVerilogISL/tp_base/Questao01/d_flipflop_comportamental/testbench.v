`timescale 1ns/1ns

// Testes para a especificação comportamental
module test;
  reg clk;
  reg reset;
  reg d;
  wire q1;
  wire q2;
  
  // Instanciar o design em teste
  Dflipflop DFF(.clk(clk), .reset(reset), .D(d), .Q1(q1), .Q2(q2));
          
  initial begin
    // Gerar arquivo
    $dumpfile("dump.vcd");
    $dumpvars(1);
    
    // Reset do flip-flop
    clk = 0;
    reset = 1;
    d = 1'bx;
    display;
    #5;
    
    // Liberar o reset
    d = 1;
    reset = 0;
    display;
    #5;

    // Alternar o clock
    clk = 1;
    display;
    #5;
    clk = 0;
    display;
    #5;
    clk = 1;
    display;
    #5;
    clk = 0;
    display;
    #5;
    
    // Encerrar a simulação
    $finish;
  end
  
  task display;
    #1 $display("d:%0h, q1:%0h, q2:%0h", d, q1, q2);
  endtask

endmodule