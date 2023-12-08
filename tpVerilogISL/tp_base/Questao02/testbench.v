module test;
  reg [311:0] mensagem_cifrada; // Armazena a mensagem cifrada
  reg [311:0] mensagem_original; // Armazena a mensagem de entrada

  reg clk;
  reg S1;
  reg S2;
  reg [7:0] chave; 
  wire digito_chave; // Digito da chave

  integer aux; // Variavel auxiliar para estruturas

  reg_streamcipher otp(.clk(clk), .S1(S1), .S2(S2), .entrada(chave), .saida_d(digito_chave));

  // Inverte o sinal de clock a cada 10 unidades de tempo
  always begin
    #10
    clk = ~clk;
  end

  initial begin
    $dumpfile("dump.vcd");
    $dumpvars;

    clk = 1'b0;
    
    manipula_chave(8'b11110000); // Chave escolhida para cifragem/decifragem da mensagem

    // Efetua a cifragem a mensagem
    cifragem(312'b010101000110010101110011011101000110010100100000011101000111001001100001011000100110000101101100011010000110111100100000011100000111001001100001011101000110100101100011011011110010000001110011011010010111001101110100011001010110110101100001011100110010000001101100011011110110011101101001011000110110111101110011);
    
    manipula_chave(8'b11110000);

    // Efetua a decifragem a mensagem
    decifragem;

    // Imprime os resultados
    resultados;

    $finish;
  end
  
  // Função para manipular a chave
  task manipula_chave(input [7:0] seed);
    begin
      S1 = 1'b1;
      S2 = 1'b1;
      chave = seed;
      #20
      S1 = 1'b0; // Desativa o sinal
    end
  endtask

  // Função para efetuar a cifragem da mensagem
  task cifragem(input [311:0] msg);
    begin
      for (aux = 311; aux >= 0; aux = aux - 1) begin
        #20
        mensagem_cifrada[aux] = msg[aux] ^ digito_chave; // Cifragem XOR
      end
    end
  endtask 
  
  // Função para decifragem da mensagem cifrada
  task decifragem;
    begin
      for (aux = 311; aux >= 0; aux = aux - 1) begin
        #20
        mensagem_original[aux] = mensagem_cifrada[aux] ^ digito_chave; // Decifragem XOR
      end
    end
  endtask
  
  task resultados;
    begin
      $display("\nMensagem cifrada: %s", mensagem_cifrada);
      $display("Mensagem original: %s", mensagem_original);
    end
  endtask
      
endmodule