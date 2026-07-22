`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 25.04.2024 19:14:12
// Design Name: 
// Module Name: top
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
module top #(parameter div = 50_000_000)(input clk, rst, inc, dec, output [7 : 0] leds);

clkDiv #(.div(div)) clkD(.clk(clk), .rst(rst), .tick(tick));

register adder(.clk(clk), .rst(rst), .en(tick), .inc(inc), .dec(dec), .leds(leds));

endmodule

/////////////////////

// Shift Reg
module topShift #(parameter div = 50_000_000)(input clk, rst, start, output [7 : 0] leds);

clkDiv #(.div(div)) clkD(.clk(clk), .rst(rst), .tick(tick));

shiftReg shReg(.clk(clk), .rst(rst), .en(tick), .start(start & status), .sig(sig));

leds l(.clk(clk), .rst(rst), .en(tick), .sig(sig), .status(status), .leds(leds));

endmodule


/////////////////////

// All Lights
module topLight#(parameter div = 50_000_000)(input clk, rst, start, output [7 : 0] leds);

clkDiv #(.div(div)) clkD(.clk(clk), .rst(rst), .tick(tick));

lightReg lr(.clk(clk), .rst(rst), .en(tick), .start(status & start), .sig(sig));

light ligh(.clk(clk), .rst(rst), .en(tick), .sig(sig), .status(status), .leds(leds));

endmodule

