`timescale 1ns/1ns

// Testes para a especificação descritiva
module test;
  reg clk;
  reg reset;
  reg D;
  wire Q;
  
  // Instanciar o design em teste
  Dflipflop DFF(.clk(clk), .reset(reset), .D(D), .Q(Q));
          
  initial begin
    // Gerar arquivo
    $dumpfile("dump.vcd");
    $dumpvars(1);
    
    // Reset do flip-flop
    clk = 0;
    reset = 1;
    D = 1'bx;
    display();
    #5;
    
    // Liberar o reset
    D = 1;
    reset = 0;
    display();
    #5;

    // Alternar o clock
    clk = 1;
    display();
    #5;
    clk = 0;
    display();
    #5;
    clk = 1;
    display();
    #5;
    clk = 0;
    display();
    #5;
    
    // Encerrar a simulação
    $finish;
  end
  
  task display;
    #1 $display("D:%0h, Q:%0h", D, Q);
  endtask

endmodule
