`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 22.05.2024 22:21:10
// Design Name: 
// Module Name: tb
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module tb();

logic clk, rst;
wire HD_SDA, HD_SCL;

wire DBG_SDA, DBG_SCL;

//wire [15 : 0] Pixel;

top t(
    .clk(clk),
    .rst(rst),
    .HD_SDA(HD_SDA),
    .HD_SCL(HD_SCL),
    
//    .Pixel(Pixel));

    .DBG_SCL(DBG_SCL),
    .DBG_SDA(DBG_SDA));
    

logic setSDAOnAck;

initial begin
    #0 clk = 1'b0;
    forever #1 clk = ~clk;
end

initial begin
    #1 rst = 1'b0;
    #10 rst = 1'b1;
    #1 rst = 1'b0;
    
    #1_000_000 rst = 1'b1;
    #1 rst = 1'b0;
end

//initial begin
//    #0 en = 1'b0;
//    #5 en = 1'b1;
//    #1 en = 1'b0;
    
//    #1000 en = 1'b1;
//    #5 en = 1'b0;
//end

initial begin
    #0 setSDAOnAck = 1'bz;
    
    #200_000 setSDAOnAck = 1'b0;
    #20_000 setSDAOnAck = 1'bz;
    
    for (int i = 0; i < 4; i++) begin 
        #160_000 setSDAOnAck = 1'b0;
        #20_000 setSDAOnAck = 1'bz;
    end
     
    #260_000 setSDAOnAck <= 1'b0;
    #20_000 setSDAOnAck = 1'bz;

    forever begin 
        #160_000 setSDAOnAck = 1'b0;
        #20_000 setSDAOnAck = 1'bz;
    end
end

initial begin
    #7_100_000 $finish;
end

assign HD_SDA = setSDAOnAck;

endmodule
