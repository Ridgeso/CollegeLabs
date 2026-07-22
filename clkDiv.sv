`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 25.04.2024 19:11:56
// Design Name: 
// Module Name: clkDiv
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


module clkDiv #(parameter div = 100)(input clk, rst, output tick);

localparam nb = $clog2(div) - 1;
logic [nb : 0] counter;

always @(posedge clk, posedge rst)
    if (rst)
        counter <= {nb{1'b0}};
    else if (div - 1 == counter)
        counter <= {nb{1'b0}};
    else
        counter <= counter + 1'b1;

assign tick = div - 1 == counter;

endmodule

