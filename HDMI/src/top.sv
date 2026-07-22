`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 22.05.2024 22:19:46
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


module top(
    input clk,
    input hClk,
    input rst,
    
    inout HD_SDA,
    output HD_SCL,
//    output HD_CLK,
//    output HD_DE,
//    output HD_HSYNC,
//    output HD_VSYNC,
//    output [15 : 0] HD_D,

    // DEBUG
    output DBG_SDA,
    output DBG_SCL);
    

enabler #(.delay(2)) en_generator(
    .clk(clk),
    .rst(rst),
    .slow_rise(slow_rise),
    .en(en));

slow_clk #(.div(2500)) clk_div(
    .clk(clk),
    .rst(rst),
    .slow_rise(slow_rise),
    .slow_fall(slow_fall));

i2c_fsm i2cFsm(
    .clk(clk),
    .rst(rst),
    .slow_rise(slow_rise),
    .slow_fall(slow_fall),
    .en(en),
    .HD_SDA(HD_SDA),
    .HD_SCL(HD_SCL),
    
    .done(initDone),
    
    // DEBUG
    .DBG_SCL(DBG_SCL),
    .DBG_SDA(DBG_SDA));

//hdmi hdmi(
//    .clk(hClk),
//    .rst(rst),
//    .en(initDone),
    
//    .HD_CLK(HD_CLK),
//    .HD_DE(HD_DE),
//    .HD_HSYNC(HD_HSYNC),
//    .HD_VSYNC(HD_VSYNC),
//    .HD_D(HD_D));

endmodule
