// ==============================================================
// RTL generated by Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Version: 2022.2
// Copyright (C) Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

(* CORE_GENERATION_INFO="ChaCha20XOR_ChaCha20XOR,hls_ip_2022_2,{HLS_INPUT_TYPE=cxx,HLS_INPUT_FLOAT=0,HLS_INPUT_FIXED=0,HLS_INPUT_PART=xc7z007s-clg400-1,HLS_INPUT_CLOCK=10.000000,HLS_INPUT_ARCH=others,HLS_SYN_CLOCK=7.196000,HLS_SYN_LAT=-1,HLS_SYN_TPT=none,HLS_SYN_MEM=0,HLS_SYN_DSP=0,HLS_SYN_FF=3928,HLS_SYN_LUT=5863,HLS_VERSION=2022_2}" *)

module ChaCha20XOR (
        ap_clk,
        ap_rst_n,
        s_axi_control_AWVALID,
        s_axi_control_AWREADY,
        s_axi_control_AWADDR,
        s_axi_control_WVALID,
        s_axi_control_WREADY,
        s_axi_control_WDATA,
        s_axi_control_WSTRB,
        s_axi_control_ARVALID,
        s_axi_control_ARREADY,
        s_axi_control_ARADDR,
        s_axi_control_RVALID,
        s_axi_control_RREADY,
        s_axi_control_RDATA,
        s_axi_control_RRESP,
        s_axi_control_BVALID,
        s_axi_control_BREADY,
        s_axi_control_BRESP,
        interrupt
);

parameter    ap_ST_fsm_state1 = 8'd1;
parameter    ap_ST_fsm_state2 = 8'd2;
parameter    ap_ST_fsm_state3 = 8'd4;
parameter    ap_ST_fsm_state4 = 8'd8;
parameter    ap_ST_fsm_state5 = 8'd16;
parameter    ap_ST_fsm_state6 = 8'd32;
parameter    ap_ST_fsm_state7 = 8'd64;
parameter    ap_ST_fsm_state8 = 8'd128;
parameter    C_S_AXI_CONTROL_DATA_WIDTH = 32;
parameter    C_S_AXI_CONTROL_ADDR_WIDTH = 9;
parameter    C_S_AXI_DATA_WIDTH = 32;

parameter C_S_AXI_CONTROL_WSTRB_WIDTH = (32 / 8);
parameter C_S_AXI_WSTRB_WIDTH = (32 / 8);

input   ap_clk;
input   ap_rst_n;
input   s_axi_control_AWVALID;
output   s_axi_control_AWREADY;
input  [C_S_AXI_CONTROL_ADDR_WIDTH - 1:0] s_axi_control_AWADDR;
input   s_axi_control_WVALID;
output   s_axi_control_WREADY;
input  [C_S_AXI_CONTROL_DATA_WIDTH - 1:0] s_axi_control_WDATA;
input  [C_S_AXI_CONTROL_WSTRB_WIDTH - 1:0] s_axi_control_WSTRB;
input   s_axi_control_ARVALID;
output   s_axi_control_ARREADY;
input  [C_S_AXI_CONTROL_ADDR_WIDTH - 1:0] s_axi_control_ARADDR;
output   s_axi_control_RVALID;
input   s_axi_control_RREADY;
output  [C_S_AXI_CONTROL_DATA_WIDTH - 1:0] s_axi_control_RDATA;
output  [1:0] s_axi_control_RRESP;
output   s_axi_control_BVALID;
input   s_axi_control_BREADY;
output  [1:0] s_axi_control_BRESP;
output   interrupt;

 reg    ap_rst_n_inv;
wire    ap_start;
reg    ap_done;
reg    ap_idle;
(* fsm_encoding = "none" *) reg   [7:0] ap_CS_fsm;
wire    ap_CS_fsm_state1;
reg    ap_ready;
wire   [7:0] key_q0;
wire   [31:0] counter;
wire   [7:0] nonce_q0;
wire   [6:0] in_r_address0;
reg    in_r_ce0;
wire   [7:0] in_r_q0;
wire   [6:0] out_r_address0;
reg    out_r_ce0;
reg    out_r_we0;
wire   [7:0] out_r_d0;
wire   [31:0] inlen;
reg  signed [31:0] inlen_read_reg_356;
reg   [31:0] counter_read_reg_361;
wire   [26:0] select_ln159_1_fu_266_p3;
reg   [26:0] select_ln159_1_reg_366;
wire    ap_CS_fsm_state2;
wire  signed [63:0] sext_ln159_fu_279_p1;
reg  signed [63:0] sext_ln159_reg_376;
wire  signed [63:0] sext_ln159_2_fu_289_p1;
reg  signed [63:0] sext_ln159_2_reg_381;
wire   [63:0] indvars_iv_next_fu_308_p2;
reg   [63:0] indvars_iv_next_reg_392;
wire    ap_CS_fsm_state6;
wire    ap_CS_fsm_state7;
wire   [0:0] icmp_ln164_fu_313_p2;
wire   [0:0] icmp_ln166_fu_318_p2;
wire   [63:0] add_ln164_fu_332_p2;
reg   [63:0] add_ln164_reg_414;
reg   [3:0] s_address0;
reg    s_ce0;
reg    s_we0;
reg   [31:0] s_d0;
wire   [31:0] s_q0;
reg    s_ce1;
wire   [31:0] s_q1;
reg   [5:0] block_address0;
reg    block_ce0;
reg    block_we0;
wire   [7:0] block_q0;
reg    block_ce1;
reg    block_we1;
wire    grp_chacha20_init_state_fu_182_ap_start;
wire    grp_chacha20_init_state_fu_182_ap_done;
wire    grp_chacha20_init_state_fu_182_ap_idle;
wire    grp_chacha20_init_state_fu_182_ap_ready;
wire   [3:0] grp_chacha20_init_state_fu_182_s_address0;
wire    grp_chacha20_init_state_fu_182_s_ce0;
wire    grp_chacha20_init_state_fu_182_s_we0;
wire   [31:0] grp_chacha20_init_state_fu_182_s_d0;
wire   [4:0] grp_chacha20_init_state_fu_182_key_address0;
wire    grp_chacha20_init_state_fu_182_key_ce0;
wire   [3:0] grp_chacha20_init_state_fu_182_nonce_address0;
wire    grp_chacha20_init_state_fu_182_nonce_ce0;
wire    grp_chacha20_block_fu_194_ap_start;
wire    grp_chacha20_block_fu_194_ap_done;
wire    grp_chacha20_block_fu_194_ap_idle;
wire    grp_chacha20_block_fu_194_ap_ready;
wire   [3:0] grp_chacha20_block_fu_194_in_r_address0;
wire    grp_chacha20_block_fu_194_in_r_ce0;
wire   [3:0] grp_chacha20_block_fu_194_in_r_address1;
wire    grp_chacha20_block_fu_194_in_r_ce1;
wire   [5:0] grp_chacha20_block_fu_194_out_r_address0;
wire    grp_chacha20_block_fu_194_out_r_ce0;
wire    grp_chacha20_block_fu_194_out_r_we0;
wire   [7:0] grp_chacha20_block_fu_194_out_r_d0;
wire   [5:0] grp_chacha20_block_fu_194_out_r_address1;
wire    grp_chacha20_block_fu_194_out_r_ce1;
wire    grp_chacha20_block_fu_194_out_r_we1;
wire   [7:0] grp_chacha20_block_fu_194_out_r_d1;
reg   [63:0] j_1_reg_170;
wire    ap_CS_fsm_state8;
reg    grp_chacha20_init_state_fu_182_ap_start_reg;
reg    grp_chacha20_block_fu_194_ap_start_reg;
wire    ap_CS_fsm_state3;
wire   [0:0] icmp_ln159_fu_296_p2;
wire    ap_CS_fsm_state4;
wire   [63:0] zext_ln169_fu_327_p1;
reg   [63:0] j_fu_96;
wire    ap_CS_fsm_state5;
wire   [31:0] add_ln162_fu_301_p2;
wire  signed [31:0] sext_ln159_1_fu_200_p0;
wire  signed [31:0] tmp_fu_204_p1;
wire  signed [32:0] sext_ln159_1_fu_200_p1;
wire   [32:0] add_ln159_fu_212_p2;
wire   [32:0] sub_ln159_fu_226_p2;
wire   [26:0] p_lshr_fu_232_p4;
wire   [0:0] tmp_1_fu_218_p3;
wire   [26:0] sub_ln159_1_fu_242_p2;
wire   [26:0] tmp_2_fu_248_p4;
wire   [0:0] tmp_fu_204_p3;
wire   [26:0] select_ln159_fu_258_p3;
wire   [32:0] tmp_3_fu_282_p3;
wire   [5:0] trunc_ln164_fu_323_p1;
reg   [7:0] ap_NS_fsm;
reg    ap_ST_fsm_state1_blk;
reg    ap_ST_fsm_state2_blk;
wire    ap_ST_fsm_state3_blk;
reg    ap_ST_fsm_state4_blk;
wire    ap_ST_fsm_state5_blk;
wire    ap_ST_fsm_state6_blk;
wire    ap_ST_fsm_state7_blk;
wire    ap_ST_fsm_state8_blk;
wire    ap_ce_reg;

// power-on initialization
initial begin
#0 ap_CS_fsm = 8'd1;
#0 grp_chacha20_init_state_fu_182_ap_start_reg = 1'b0;
#0 grp_chacha20_block_fu_194_ap_start_reg = 1'b0;
end

ChaCha20XOR_s_RAM_AUTO_1R1W #(
    .DataWidth( 32 ),
    .AddressRange( 16 ),
    .AddressWidth( 4 ))
s_U(
    .clk(ap_clk),
    .reset(ap_rst_n_inv),
    .address0(s_address0),
    .ce0(s_ce0),
    .we0(s_we0),
    .d0(s_d0),
    .q0(s_q0),
    .address1(grp_chacha20_block_fu_194_in_r_address1),
    .ce1(s_ce1),
    .q1(s_q1)
);

ChaCha20XOR_block_RAM_AUTO_1R1W #(
    .DataWidth( 8 ),
    .AddressRange( 64 ),
    .AddressWidth( 6 ))
block_U(
    .clk(ap_clk),
    .reset(ap_rst_n_inv),
    .address0(block_address0),
    .ce0(block_ce0),
    .we0(block_we0),
    .d0(grp_chacha20_block_fu_194_out_r_d0),
    .q0(block_q0),
    .address1(grp_chacha20_block_fu_194_out_r_address1),
    .ce1(block_ce1),
    .we1(block_we1),
    .d1(grp_chacha20_block_fu_194_out_r_d1)
);

ChaCha20XOR_chacha20_init_state grp_chacha20_init_state_fu_182(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst_n_inv),
    .ap_start(grp_chacha20_init_state_fu_182_ap_start),
    .ap_done(grp_chacha20_init_state_fu_182_ap_done),
    .ap_idle(grp_chacha20_init_state_fu_182_ap_idle),
    .ap_ready(grp_chacha20_init_state_fu_182_ap_ready),
    .s_address0(grp_chacha20_init_state_fu_182_s_address0),
    .s_ce0(grp_chacha20_init_state_fu_182_s_ce0),
    .s_we0(grp_chacha20_init_state_fu_182_s_we0),
    .s_d0(grp_chacha20_init_state_fu_182_s_d0),
    .key_address0(grp_chacha20_init_state_fu_182_key_address0),
    .key_ce0(grp_chacha20_init_state_fu_182_key_ce0),
    .key_q0(key_q0),
    .counter(counter_read_reg_361),
    .nonce_address0(grp_chacha20_init_state_fu_182_nonce_address0),
    .nonce_ce0(grp_chacha20_init_state_fu_182_nonce_ce0),
    .nonce_q0(nonce_q0)
);

ChaCha20XOR_chacha20_block grp_chacha20_block_fu_194(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst_n_inv),
    .ap_start(grp_chacha20_block_fu_194_ap_start),
    .ap_done(grp_chacha20_block_fu_194_ap_done),
    .ap_idle(grp_chacha20_block_fu_194_ap_idle),
    .ap_ready(grp_chacha20_block_fu_194_ap_ready),
    .in_r_address0(grp_chacha20_block_fu_194_in_r_address0),
    .in_r_ce0(grp_chacha20_block_fu_194_in_r_ce0),
    .in_r_q0(s_q0),
    .in_r_address1(grp_chacha20_block_fu_194_in_r_address1),
    .in_r_ce1(grp_chacha20_block_fu_194_in_r_ce1),
    .in_r_q1(s_q1),
    .out_r_address0(grp_chacha20_block_fu_194_out_r_address0),
    .out_r_ce0(grp_chacha20_block_fu_194_out_r_ce0),
    .out_r_we0(grp_chacha20_block_fu_194_out_r_we0),
    .out_r_d0(grp_chacha20_block_fu_194_out_r_d0),
    .out_r_address1(grp_chacha20_block_fu_194_out_r_address1),
    .out_r_ce1(grp_chacha20_block_fu_194_out_r_ce1),
    .out_r_we1(grp_chacha20_block_fu_194_out_r_we1),
    .out_r_d1(grp_chacha20_block_fu_194_out_r_d1)
);

ChaCha20XOR_control_s_axi #(
    .C_S_AXI_ADDR_WIDTH( C_S_AXI_CONTROL_ADDR_WIDTH ),
    .C_S_AXI_DATA_WIDTH( C_S_AXI_CONTROL_DATA_WIDTH ))
control_s_axi_U(
    .AWVALID(s_axi_control_AWVALID),
    .AWREADY(s_axi_control_AWREADY),
    .AWADDR(s_axi_control_AWADDR),
    .WVALID(s_axi_control_WVALID),
    .WREADY(s_axi_control_WREADY),
    .WDATA(s_axi_control_WDATA),
    .WSTRB(s_axi_control_WSTRB),
    .ARVALID(s_axi_control_ARVALID),
    .ARREADY(s_axi_control_ARREADY),
    .ARADDR(s_axi_control_ARADDR),
    .RVALID(s_axi_control_RVALID),
    .RREADY(s_axi_control_RREADY),
    .RDATA(s_axi_control_RDATA),
    .RRESP(s_axi_control_RRESP),
    .BVALID(s_axi_control_BVALID),
    .BREADY(s_axi_control_BREADY),
    .BRESP(s_axi_control_BRESP),
    .ACLK(ap_clk),
    .ARESET(ap_rst_n_inv),
    .ACLK_EN(1'b1),
    .counter(counter),
    .inlen(inlen),
    .key_address0(grp_chacha20_init_state_fu_182_key_address0),
    .key_ce0(grp_chacha20_init_state_fu_182_key_ce0),
    .key_q0(key_q0),
    .nonce_address0(grp_chacha20_init_state_fu_182_nonce_address0),
    .nonce_ce0(grp_chacha20_init_state_fu_182_nonce_ce0),
    .nonce_q0(nonce_q0),
    .in_r_address0(in_r_address0),
    .in_r_ce0(in_r_ce0),
    .in_r_q0(in_r_q0),
    .out_r_address0(out_r_address0),
    .out_r_ce0(out_r_ce0),
    .out_r_we0(out_r_we0),
    .out_r_d0(out_r_d0),
    .ap_start(ap_start),
    .interrupt(interrupt),
    .ap_ready(ap_ready),
    .ap_done(ap_done),
    .ap_idle(ap_idle)
);

always @ (posedge ap_clk) begin
    if (ap_rst_n_inv == 1'b1) begin
        ap_CS_fsm <= ap_ST_fsm_state1;
    end else begin
        ap_CS_fsm <= ap_NS_fsm;
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst_n_inv == 1'b1) begin
        grp_chacha20_block_fu_194_ap_start_reg <= 1'b0;
    end else begin
        if (((icmp_ln159_fu_296_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state3))) begin
            grp_chacha20_block_fu_194_ap_start_reg <= 1'b1;
        end else if ((grp_chacha20_block_fu_194_ap_ready == 1'b1)) begin
            grp_chacha20_block_fu_194_ap_start_reg <= 1'b0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst_n_inv == 1'b1) begin
        grp_chacha20_init_state_fu_182_ap_start_reg <= 1'b0;
    end else begin
        if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
            grp_chacha20_init_state_fu_182_ap_start_reg <= 1'b1;
        end else if ((grp_chacha20_init_state_fu_182_ap_ready == 1'b1)) begin
            grp_chacha20_init_state_fu_182_ap_start_reg <= 1'b0;
        end
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state8)) begin
        j_1_reg_170 <= add_ln164_reg_414;
    end else if ((1'b1 == ap_CS_fsm_state6)) begin
        j_1_reg_170 <= j_fu_96;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
        j_fu_96 <= 64'd0;
    end else if (((1'b1 == ap_CS_fsm_state7) & ((icmp_ln166_fu_318_p2 == 1'd0) | (icmp_ln164_fu_313_p2 == 1'd0)))) begin
        j_fu_96 <= indvars_iv_next_reg_392;
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln166_fu_318_p2 == 1'd1) & (icmp_ln164_fu_313_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state7))) begin
        add_ln164_reg_414 <= add_ln164_fu_332_p2;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state1)) begin
        counter_read_reg_361 <= counter;
        inlen_read_reg_356 <= inlen;
        select_ln159_1_reg_366 <= select_ln159_1_fu_266_p3;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state6)) begin
        indvars_iv_next_reg_392 <= indvars_iv_next_fu_308_p2;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state2)) begin
        sext_ln159_2_reg_381[63 : 6] <= sext_ln159_2_fu_289_p1[63 : 6];
        sext_ln159_reg_376 <= sext_ln159_fu_279_p1;
    end
end

always @ (*) begin
    if ((ap_start == 1'b0)) begin
        ap_ST_fsm_state1_blk = 1'b1;
    end else begin
        ap_ST_fsm_state1_blk = 1'b0;
    end
end

always @ (*) begin
    if ((grp_chacha20_init_state_fu_182_ap_done == 1'b0)) begin
        ap_ST_fsm_state2_blk = 1'b1;
    end else begin
        ap_ST_fsm_state2_blk = 1'b0;
    end
end

assign ap_ST_fsm_state3_blk = 1'b0;

always @ (*) begin
    if ((grp_chacha20_block_fu_194_ap_done == 1'b0)) begin
        ap_ST_fsm_state4_blk = 1'b1;
    end else begin
        ap_ST_fsm_state4_blk = 1'b0;
    end
end

assign ap_ST_fsm_state5_blk = 1'b0;

assign ap_ST_fsm_state6_blk = 1'b0;

assign ap_ST_fsm_state7_blk = 1'b0;

assign ap_ST_fsm_state8_blk = 1'b0;

always @ (*) begin
    if (((icmp_ln159_fu_296_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state3))) begin
        ap_done = 1'b1;
    end else begin
        ap_done = 1'b0;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b0))) begin
        ap_idle = 1'b1;
    end else begin
        ap_idle = 1'b0;
    end
end

always @ (*) begin
    if (((icmp_ln159_fu_296_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state3))) begin
        ap_ready = 1'b1;
    end else begin
        ap_ready = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state7)) begin
        block_address0 = zext_ln169_fu_327_p1;
    end else if ((1'b1 == ap_CS_fsm_state4)) begin
        block_address0 = grp_chacha20_block_fu_194_out_r_address0;
    end else begin
        block_address0 = 'bx;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state7)) begin
        block_ce0 = 1'b1;
    end else if ((1'b1 == ap_CS_fsm_state4)) begin
        block_ce0 = grp_chacha20_block_fu_194_out_r_ce0;
    end else begin
        block_ce0 = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state4)) begin
        block_ce1 = grp_chacha20_block_fu_194_out_r_ce1;
    end else begin
        block_ce1 = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state4)) begin
        block_we0 = grp_chacha20_block_fu_194_out_r_we0;
    end else begin
        block_we0 = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state4)) begin
        block_we1 = grp_chacha20_block_fu_194_out_r_we1;
    end else begin
        block_we1 = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state7)) begin
        in_r_ce0 = 1'b1;
    end else begin
        in_r_ce0 = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state8)) begin
        out_r_ce0 = 1'b1;
    end else begin
        out_r_ce0 = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state8)) begin
        out_r_we0 = 1'b1;
    end else begin
        out_r_we0 = 1'b0;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state6) | (1'b1 == ap_CS_fsm_state5))) begin
        s_address0 = 64'd12;
    end else if ((1'b1 == ap_CS_fsm_state4)) begin
        s_address0 = grp_chacha20_block_fu_194_in_r_address0;
    end else if ((1'b1 == ap_CS_fsm_state2)) begin
        s_address0 = grp_chacha20_init_state_fu_182_s_address0;
    end else begin
        s_address0 = 'bx;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state6) | (1'b1 == ap_CS_fsm_state5))) begin
        s_ce0 = 1'b1;
    end else if ((1'b1 == ap_CS_fsm_state4)) begin
        s_ce0 = grp_chacha20_block_fu_194_in_r_ce0;
    end else if ((1'b1 == ap_CS_fsm_state2)) begin
        s_ce0 = grp_chacha20_init_state_fu_182_s_ce0;
    end else begin
        s_ce0 = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state4)) begin
        s_ce1 = grp_chacha20_block_fu_194_in_r_ce1;
    end else begin
        s_ce1 = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state6)) begin
        s_d0 = add_ln162_fu_301_p2;
    end else if ((1'b1 == ap_CS_fsm_state2)) begin
        s_d0 = grp_chacha20_init_state_fu_182_s_d0;
    end else begin
        s_d0 = 'bx;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state6)) begin
        s_we0 = 1'b1;
    end else if ((1'b1 == ap_CS_fsm_state2)) begin
        s_we0 = grp_chacha20_init_state_fu_182_s_we0;
    end else begin
        s_we0 = 1'b0;
    end
end

always @ (*) begin
    case (ap_CS_fsm)
        ap_ST_fsm_state1 : begin
            if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end
        end
        ap_ST_fsm_state2 : begin
            if (((1'b1 == ap_CS_fsm_state2) & (grp_chacha20_init_state_fu_182_ap_done == 1'b1))) begin
                ap_NS_fsm = ap_ST_fsm_state3;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end
        end
        ap_ST_fsm_state3 : begin
            if (((icmp_ln159_fu_296_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state3))) begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state4;
            end
        end
        ap_ST_fsm_state4 : begin
            if (((1'b1 == ap_CS_fsm_state4) & (grp_chacha20_block_fu_194_ap_done == 1'b1))) begin
                ap_NS_fsm = ap_ST_fsm_state5;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state4;
            end
        end
        ap_ST_fsm_state5 : begin
            ap_NS_fsm = ap_ST_fsm_state6;
        end
        ap_ST_fsm_state6 : begin
            ap_NS_fsm = ap_ST_fsm_state7;
        end
        ap_ST_fsm_state7 : begin
            if (((1'b1 == ap_CS_fsm_state7) & ((icmp_ln166_fu_318_p2 == 1'd0) | (icmp_ln164_fu_313_p2 == 1'd0)))) begin
                ap_NS_fsm = ap_ST_fsm_state3;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state8;
            end
        end
        ap_ST_fsm_state8 : begin
            ap_NS_fsm = ap_ST_fsm_state7;
        end
        default : begin
            ap_NS_fsm = 'bx;
        end
    endcase
end

assign add_ln159_fu_212_p2 = ($signed(sext_ln159_1_fu_200_p1) + $signed(33'd63));

assign add_ln162_fu_301_p2 = (s_q0 + 32'd1);

assign add_ln164_fu_332_p2 = (j_1_reg_170 + 64'd1);

assign ap_CS_fsm_state1 = ap_CS_fsm[32'd0];

assign ap_CS_fsm_state2 = ap_CS_fsm[32'd1];

assign ap_CS_fsm_state3 = ap_CS_fsm[32'd2];

assign ap_CS_fsm_state4 = ap_CS_fsm[32'd3];

assign ap_CS_fsm_state5 = ap_CS_fsm[32'd4];

assign ap_CS_fsm_state6 = ap_CS_fsm[32'd5];

assign ap_CS_fsm_state7 = ap_CS_fsm[32'd6];

assign ap_CS_fsm_state8 = ap_CS_fsm[32'd7];

always @ (*) begin
    ap_rst_n_inv = ~ap_rst_n;
end

assign grp_chacha20_block_fu_194_ap_start = grp_chacha20_block_fu_194_ap_start_reg;

assign grp_chacha20_init_state_fu_182_ap_start = grp_chacha20_init_state_fu_182_ap_start_reg;

assign icmp_ln159_fu_296_p2 = ((j_fu_96 == sext_ln159_2_reg_381) ? 1'b1 : 1'b0);

assign icmp_ln164_fu_313_p2 = (($signed(j_1_reg_170) < $signed(indvars_iv_next_reg_392)) ? 1'b1 : 1'b0);

assign icmp_ln166_fu_318_p2 = (($signed(j_1_reg_170) < $signed(sext_ln159_reg_376)) ? 1'b1 : 1'b0);

assign in_r_address0 = j_1_reg_170;

assign indvars_iv_next_fu_308_p2 = (j_fu_96 + 64'd64);

assign out_r_address0 = j_1_reg_170;

assign out_r_d0 = (in_r_q0 ^ block_q0);

assign p_lshr_fu_232_p4 = {{sub_ln159_fu_226_p2[32:6]}};

assign select_ln159_1_fu_266_p3 = ((tmp_fu_204_p3[0:0] == 1'b1) ? 27'd0 : select_ln159_fu_258_p3);

assign select_ln159_fu_258_p3 = ((tmp_1_fu_218_p3[0:0] == 1'b1) ? sub_ln159_1_fu_242_p2 : tmp_2_fu_248_p4);

assign sext_ln159_1_fu_200_p0 = inlen;

assign sext_ln159_1_fu_200_p1 = sext_ln159_1_fu_200_p0;

assign sext_ln159_2_fu_289_p1 = $signed(tmp_3_fu_282_p3);

assign sext_ln159_fu_279_p1 = inlen_read_reg_356;

assign sub_ln159_1_fu_242_p2 = (27'd0 - p_lshr_fu_232_p4);

assign sub_ln159_fu_226_p2 = ($signed(33'd8589934529) - $signed(sext_ln159_1_fu_200_p1));

assign tmp_1_fu_218_p3 = add_ln159_fu_212_p2[32'd32];

assign tmp_2_fu_248_p4 = {{add_ln159_fu_212_p2[32:6]}};

assign tmp_3_fu_282_p3 = {{select_ln159_1_reg_366}, {6'd0}};

assign tmp_fu_204_p1 = inlen;

assign tmp_fu_204_p3 = tmp_fu_204_p1[32'd31];

assign trunc_ln164_fu_323_p1 = j_1_reg_170[5:0];

assign zext_ln169_fu_327_p1 = trunc_ln164_fu_323_p1;

always @ (posedge ap_clk) begin
    sext_ln159_2_reg_381[5:0] <= 6'b000000;
end

endmodule //ChaCha20XOR
