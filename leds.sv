`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 25.04.2024 20:07:59
// Design Name: 
// Module Name: leds
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

// Shift reg
module leds(input clk, rst, en, sig, output status, logic [7:0] leds);

always @(posedge clk, rst)
    if (rst)
        leds <= 8'b0;
    else if (en)
        leds <= {sig | leds[0], leds[7 : 1]};

assign status = 8'b0 == leds;

endmodule

//////////////////

// All Lights
module light(input clk, rst, en, sig, output status, logic [7:0] leds);

always @(posedge clk, rst)
    if (rst)
        leds <= 8'h0;
    else if (en)
        if (8'hff == leds)
            leds <= 8'h80; 
        else
            leds <= {sig | leds[7], leds[7 : 1]};

assign status = 8'h0 == leds;

endmodule