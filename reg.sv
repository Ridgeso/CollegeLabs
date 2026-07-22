`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 25.04.2024 19:03:10
// Design Name: 
// Module Name: reg
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
module register(input clk, rst, en, inc, dec, output [7 : 0] leds);

logic [7 : 0] address;

always @(posedge clk, posedge rst)
    if (rst)
        address <= 8'h80;
    else if (en)
        if (inc)
            address <= address + 1'h01;
        else if (dec)
            address <= address - 1'h01;

assign leds = address;

endmodule


/////////////

// Shift Ref
module shiftReg(input clk, rst, en, start, output sig);

typedef enum {Idle, A, B, C, D, E} State;

State state, nextState;

always @(posedge clk, posedge rst)
    if (rst)
        state <= Idle;
    else if (en)
        state <= nextState;

always @(posedge clk, posedge rst) begin
    nextState = Idle;
    case (state)
        Idle:
            if (start)
                nextState = A;
            else
                nextState = Idle;
        A: nextState = B;
        B: nextState = C;
        C: nextState = D;
        D: nextState = E;
        E: nextState = Idle;
    endcase
end
    
assign sig = A == state | C == state | E == state;

endmodule

/////////////

// All lights
module lightReg(input clk, rst, en, start, output sig);

typedef enum {Idle, A} State;

State state, nextState;

always @(posedge clk, posedge rst)
    if (rst)
        state <= Idle;
    else if (en)
        state <= nextState;

always @(posedge clk, posedge rst) begin
    nextState = Idle;
    case (state)
        Idle:
            if (start)
                nextState = A;
            else
                nextState = Idle;
        A: nextState = Idle;
    endcase
end
    
assign sig = A == state;

endmodule
