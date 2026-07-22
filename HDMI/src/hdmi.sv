`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 28.05.2024 20:06:53
// Design Name: 
// Module Name: hdmi
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


module hdmi(
    input hClk,
    input rst,
    input en,
    
    output HD_CLK,
    output HD_DE,
    output HD_HSYNC,
    output HD_VSYNC,
    output [15 : 0] HD_D);

logic [15 : 0] dataToSend;

logic [10 : 0] hCnt;
logic [10 : 0] vCnt;
logic [15 : 0] data [0 : 99][0 : 99];

initial $readmemh("image.mem", data);

assign HD_D = dataToSend;

always @(posedge hClk, posedge rst)
    if (rst)
        dataToSend <= 0;
    else
        dataToSend <= data[hCnt][vCnt];

endmodule
