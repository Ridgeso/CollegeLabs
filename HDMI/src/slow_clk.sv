`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/24/2024 10:23:17 AM
// Design Name: 
// Module Name: slow_clk
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


module slow_clk #(parameter div = 2000)(
    input clk,
    input rst,
    output slow_rise,
    output slow_fall);

localparam rise_cycle = div - 1;
localparam fall_cycle = 2 * div - 1;
localparam cycle = 2 * div;

localparam nb = $clog2(cycle);
logic [nb-1 : 0] cnt;

always @(posedge clk, posedge rst)
    if(rst)
        cnt <= {{nb}{1'b0}};
    else
        cnt <= (cnt + 1'b1) % cycle;

assign slow_rise = (cnt == rise_cycle);
assign slow_fall = (cnt == fall_cycle);

endmodule
