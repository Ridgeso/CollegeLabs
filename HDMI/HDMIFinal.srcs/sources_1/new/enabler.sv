`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/24/2024 09:49:55 AM
// Design Name: 
// Module Name: enabler
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


module enabler #(parameter delay = 5)(
    input clk,
    input rst,
    input slow_rise,
    output en);

localparam nb = $clog2(delay + 1);

logic [nb - 1 : 0] cnt;

always@(posedge clk, posedge rst)
    if(rst)
        cnt <= {{nb}{1'b0}};
    else if(slow_rise && cnt <= delay)
        cnt <= cnt + 1'b1;

assign en = delay == cnt;

endmodule
