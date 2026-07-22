`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 22.05.2024 22:13:42
// Design Name: 
// Module Name: i2c_fsm
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


module i2c_fsm(
    input clk,
    input rst,
    input slow_rise,
    input slow_fall,
    input en,
    inout HD_SDA,
    output HD_SCL,
    
    output reg done,
    
    // DEBUG
    output DBG_SDA,
    output DBG_SCL);

typedef enum {
    PreInit,
    Idle,
    SendStart,
    SendSlaveAddress,
    ReceiveSlaveAdderssAck,
    SendDataAddress,
    ReceiveDataAddressAck,
    SendData,
    ReceiveDataAck,
    SendStop
} I2CState;

I2CState cState, nState;

logic SDA, SCL;

// Variables
logic [3 : 0] saCnt;
logic [6 : 0] dataCnt;

logic secondEdge;
logic secondAckEdge;

logic [7 : 0] data [1 : 33];

logic byteSent;
logic ackReceived;
logic initializationFinished;

logic reactOnSlowRise;
logic reactOnSlowFall;
//

initial $readmemh("initData.mem", data);

always @(posedge clk, posedge rst)
    if (rst)
        cState <= Idle;
    else if(slow_rise)
        cState <= nState;

always @(posedge clk, posedge rst)
    if (rst)
        secondEdge <= 1'b0;
    else if (slow_fall) begin
        if (SendSlaveAddress == cState || SendDataAddress == cState || SendData == cState)
            secondEdge <= secondEdge + 1'b1;
        else
            secondEdge <= 1'b0;
    end
    
always @(posedge clk, posedge rst)
    if (rst)
        secondAckEdge <= 1'b0;
    else if (slow_rise) begin
        if (ReceiveSlaveAdderssAck == cState || ReceiveDataAddressAck == cState || ReceiveDataAck == cState)
            secondAckEdge  <= 1'b1;
        else
            secondAckEdge <= 1'b0;
    end
    
always @(posedge clk, posedge rst)
    if (rst)
        saCnt <= 0;
    else if (slow_fall) begin
        if (4'b1000 == saCnt)
            saCnt <= 1'b0;
        else if(secondEdge) begin
            if (SendSlaveAddress == cState)
                saCnt <= saCnt + 1'b1;
            else if (SendDataAddress == cState)
                saCnt <= saCnt + 1'b1;
            else if (SendData == cState)
                saCnt <= saCnt + 1'b1;
        end
    end
        
always @(posedge clk, posedge rst)
    if (rst)
        dataCnt <= 1;
    else if (byteSent && slow_rise)
        dataCnt <= dataCnt + 1'b1;
        
always @(posedge clk, posedge rst)
    if (rst)
        done <= 1'b0;
    else if (Idle == cState && initializationFinished && slow_rise)
        done <= 1'b1;

always @(posedge clk) begin
    nState = Idle;
    case (cState)
        PreInit: nState = Idle;
        Idle: nState = en ? SendStart : Idle;
        SendStart: nState = SendSlaveAddress;
        SendSlaveAddress: nState = byteSent ? ReceiveSlaveAdderssAck : SendSlaveAddress;
        ReceiveSlaveAdderssAck: nState = 
              !secondAckEdge ? ReceiveSlaveAdderssAck
            : ackReceived    ? SendDataAddress
                             : SendStop;
        SendDataAddress: nState = byteSent ? ReceiveDataAddressAck : SendDataAddress;
        ReceiveDataAddressAck: nState =
              !secondAckEdge ? ReceiveDataAddressAck
            : ackReceived    ? SendData
                             : SendStop;
        SendData: nState = byteSent ? ReceiveDataAck : SendData;
        ReceiveDataAck: nState =
              !secondAckEdge         ? ReceiveDataAck 
            : initializationFinished ? SendStop
            : ackReceived            ? SendDataAddress
                                     : SendStop;
        SendStop: nState = Idle;
    endcase
end

always @(posedge clk, posedge rst) begin
    if (rst)
        SDA <= 1'b1;
    else if (slow_fall) begin
        SDA = 1'b1;
        case (cState)
            Idle: SDA = 1'b1;
            SendStart: SDA = 1'b0;
            SendSlaveAddress: SDA = byteSent ? 1'bz : data[dataCnt][7 - saCnt];
            ReceiveSlaveAdderssAck: SDA = 1'bz;
            SendDataAddress: SDA = byteSent ? 1'bz : data[dataCnt][7 - saCnt];
            ReceiveDataAddressAck: SDA = 1'bz;
            SendData: SDA = byteSent ? 1'bz : data[dataCnt][7 - saCnt];
            ReceiveDataAck: SDA = 1'bz;
            SendStop: SDA = 1'b0;
        endcase
    end
end

always @(posedge clk, posedge rst) begin
    if (rst)
        SCL <= 1'b1;
    else if (slow_rise) begin
        if (Idle == cState || SendStop == cState)
            SCL <= 1'b1;
        else if (SendStart == cState)
            SCL <= 1'b0;
        else
            SCL <= ~SCL;
    end
end

assign byteSent = 4'b1000 == saCnt;
assign ackReceived = (
    ReceiveSlaveAdderssAck == cState ||
        ReceiveDataAddressAck == cState ||
        ReceiveDataAck == cState) &&
    1'b0 == HD_SDA;
assign initializationFinished = 6'b100010 == dataCnt;

assign HD_SDA = SDA;
assign HD_SCL = SCL;

// DEBUG
assign DBG_SDA = SDA;
assign DBG_SCL = SCL;

endmodule
