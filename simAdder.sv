`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 25.04.2024 19:23:27
// Design Name: 
// Module Name: simAdder
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

// Adder
module simAdder();

logic clk, rst, inc, dec;
logic [7 : 0] leds;

top #(.div(10)) topSim (.clk(clk), .rst(rst), .inc(inc), .dec(dec), .leds(leds));

initial begin
    rst = 1'b0;
    #2 rst = 1'b1;
    #3 rst = 1'b0;
end

initial begin
    clk = 1'b0;
    forever #5 clk = ~clk;
end

initial begin
    inc = 1'b0;
    dec = 1'b0;

    #85 inc = 1'b1;
    #295 inc = 1'b0;
    
    #320 dec = 1'b1;
    #430 dec = 1'b0;
end

endmodule

/////////////

// Shift Reg
module simShiftReg();

logic clk, rst, start;
logic [7 : 0] leds;

topShift #(.div(5)) tbShift(.clk(clk), .rst(rst), .start(start), .leds(leds));

initial begin
    clk = 1'b0;
    forever #5 clk = ~clk;
end

initial begin
    rst = 1'b0;
    #2 rst = 1'b1;
    #3 rst = 1'b0;
    
    #600 rst = 1'b1;
    #5 rst = 1'b0;
end

initial begin
    start = 1'b0;
    #35 start = 1'b1;
    #5 start = 1'b0;
end

endmodule


/////////////

// All lights
module simAllLights();

logic clk, rst, start;
logic [7 : 0] leds;

topLight #(.div(5)) tbLight(.clk(clk), .rst(rst), .start(start), .leds(leds));

initial begin
    clk = 1'b0;
    forever #5 clk = ~clk;
end

initial begin
    rst = 1'b0;
    #2 rst = 1'b1;
    #3 rst = 1'b0;
    
    #600 rst = 1'b1;
    #5 rst = 1'b0;
end

initial begin
    start = 1'b0;
    #35 start = 1'b1;
    #5 start = 1'b0;
end

endmodule

