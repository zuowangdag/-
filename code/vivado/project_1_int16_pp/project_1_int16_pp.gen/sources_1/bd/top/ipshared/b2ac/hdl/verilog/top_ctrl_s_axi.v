// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
`timescale 1ns/1ps
module top_ctrl_s_axi
#(parameter
    C_S_AXI_ADDR_WIDTH = 8,
    C_S_AXI_DATA_WIDTH = 32
)(
    input  wire                          ACLK,
    input  wire                          ARESET,
    input  wire                          ACLK_EN,
    input  wire [C_S_AXI_ADDR_WIDTH-1:0] AWADDR,
    input  wire                          AWVALID,
    output wire                          AWREADY,
    input  wire [C_S_AXI_DATA_WIDTH-1:0] WDATA,
    input  wire [C_S_AXI_DATA_WIDTH/8-1:0] WSTRB,
    input  wire                          WVALID,
    output wire                          WREADY,
    output wire [1:0]                    BRESP,
    output wire                          BVALID,
    input  wire                          BREADY,
    input  wire [C_S_AXI_ADDR_WIDTH-1:0] ARADDR,
    input  wire                          ARVALID,
    output wire                          ARREADY,
    output wire [C_S_AXI_DATA_WIDTH-1:0] RDATA,
    output wire [1:0]                    RRESP,
    output wire                          RVALID,
    input  wire                          RREADY,
    output wire                          interrupt,
    output wire [31:0]                   ifm_offset,
    output wire [31:0]                   ofm_offset,
    output wire [31:0]                   weights_offset,
    output wire [31:0]                   bias_offset,
    output wire [15:0]                   ifm_ch,
    output wire [15:0]                   ifm_h,
    output wire [15:0]                   ifm_w,
    output wire [15:0]                   ofm_ch,
    output wire [15:0]                   ofm_h,
    output wire [15:0]                   ofm_w,
    output wire [7:0]                    I_CH,
    output wire [7:0]                    I_H,
    output wire [7:0]                    I_W,
    output wire [7:0]                    O_CH,
    output wire [7:0]                    O_H,
    output wire [7:0]                    O_W,
    output wire [7:0]                    ker_size,
    output wire [7:0]                    stride,
    output wire [7:0]                    padding,
    output wire [7:0]                    layer_type,
    output wire [0:0]                    act_silu,
    output wire [15:0]                   CNT,
    output wire [7:0]                    ifm_q1,
    output wire [7:0]                    ifm_q2,
    output wire [7:0]                    weights_q,
    output wire [7:0]                    bias_q,
    output wire [7:0]                    ofm_q_before_act,
    output wire [7:0]                    ofm_q_after_q,
    output wire                          ap_start,
    input  wire                          ap_done,
    input  wire                          ap_ready,
    input  wire                          ap_idle
);
//------------------------Address Info-------------------
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read/COR)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read)
//        bit 7  - auto_restart (Read/Write)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0  - enable ap_done interrupt (Read/Write)
//        bit 1  - enable ap_ready interrupt (Read/Write)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/TOW)
//        bit 0  - ap_done (COR/TOW)
//        bit 1  - ap_ready (COR/TOW)
//        others - reserved
// 0x10 : Data signal of ifm_offset
//        bit 31~0 - ifm_offset[31:0] (Read/Write)
// 0x14 : reserved
// 0x18 : Data signal of ofm_offset
//        bit 31~0 - ofm_offset[31:0] (Read/Write)
// 0x1c : reserved
// 0x20 : Data signal of weights_offset
//        bit 31~0 - weights_offset[31:0] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of bias_offset
//        bit 31~0 - bias_offset[31:0] (Read/Write)
// 0x2c : reserved
// 0x30 : Data signal of ifm_ch
//        bit 15~0 - ifm_ch[15:0] (Read/Write)
//        others   - reserved
// 0x34 : reserved
// 0x38 : Data signal of ifm_h
//        bit 15~0 - ifm_h[15:0] (Read/Write)
//        others   - reserved
// 0x3c : reserved
// 0x40 : Data signal of ifm_w
//        bit 15~0 - ifm_w[15:0] (Read/Write)
//        others   - reserved
// 0x44 : reserved
// 0x48 : Data signal of ofm_ch
//        bit 15~0 - ofm_ch[15:0] (Read/Write)
//        others   - reserved
// 0x4c : reserved
// 0x50 : Data signal of ofm_h
//        bit 15~0 - ofm_h[15:0] (Read/Write)
//        others   - reserved
// 0x54 : reserved
// 0x58 : Data signal of ofm_w
//        bit 15~0 - ofm_w[15:0] (Read/Write)
//        others   - reserved
// 0x5c : reserved
// 0x60 : Data signal of I_CH
//        bit 7~0 - I_CH[7:0] (Read/Write)
//        others  - reserved
// 0x64 : reserved
// 0x68 : Data signal of I_H
//        bit 7~0 - I_H[7:0] (Read/Write)
//        others  - reserved
// 0x6c : reserved
// 0x70 : Data signal of I_W
//        bit 7~0 - I_W[7:0] (Read/Write)
//        others  - reserved
// 0x74 : reserved
// 0x78 : Data signal of O_CH
//        bit 7~0 - O_CH[7:0] (Read/Write)
//        others  - reserved
// 0x7c : reserved
// 0x80 : Data signal of O_H
//        bit 7~0 - O_H[7:0] (Read/Write)
//        others  - reserved
// 0x84 : reserved
// 0x88 : Data signal of O_W
//        bit 7~0 - O_W[7:0] (Read/Write)
//        others  - reserved
// 0x8c : reserved
// 0x90 : Data signal of ker_size
//        bit 7~0 - ker_size[7:0] (Read/Write)
//        others  - reserved
// 0x94 : reserved
// 0x98 : Data signal of stride
//        bit 7~0 - stride[7:0] (Read/Write)
//        others  - reserved
// 0x9c : reserved
// 0xa0 : Data signal of padding
//        bit 7~0 - padding[7:0] (Read/Write)
//        others  - reserved
// 0xa4 : reserved
// 0xa8 : Data signal of layer_type
//        bit 7~0 - layer_type[7:0] (Read/Write)
//        others  - reserved
// 0xac : reserved
// 0xb0 : Data signal of act_silu
//        bit 0  - act_silu[0] (Read/Write)
//        others - reserved
// 0xb4 : reserved
// 0xb8 : Data signal of CNT
//        bit 15~0 - CNT[15:0] (Read/Write)
//        others   - reserved
// 0xbc : reserved
// 0xc0 : Data signal of ifm_q1
//        bit 7~0 - ifm_q1[7:0] (Read/Write)
//        others  - reserved
// 0xc4 : reserved
// 0xc8 : Data signal of ifm_q2
//        bit 7~0 - ifm_q2[7:0] (Read/Write)
//        others  - reserved
// 0xcc : reserved
// 0xd0 : Data signal of weights_q
//        bit 7~0 - weights_q[7:0] (Read/Write)
//        others  - reserved
// 0xd4 : reserved
// 0xd8 : Data signal of bias_q
//        bit 7~0 - bias_q[7:0] (Read/Write)
//        others  - reserved
// 0xdc : reserved
// 0xe0 : Data signal of ofm_q_before_act
//        bit 7~0 - ofm_q_before_act[7:0] (Read/Write)
//        others  - reserved
// 0xe4 : reserved
// 0xe8 : Data signal of ofm_q_after_q
//        bit 7~0 - ofm_q_after_q[7:0] (Read/Write)
//        others  - reserved
// 0xec : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

//------------------------Parameter----------------------
localparam
    ADDR_AP_CTRL                 = 8'h00,
    ADDR_GIE                     = 8'h04,
    ADDR_IER                     = 8'h08,
    ADDR_ISR                     = 8'h0c,
    ADDR_IFM_OFFSET_DATA_0       = 8'h10,
    ADDR_IFM_OFFSET_CTRL         = 8'h14,
    ADDR_OFM_OFFSET_DATA_0       = 8'h18,
    ADDR_OFM_OFFSET_CTRL         = 8'h1c,
    ADDR_WEIGHTS_OFFSET_DATA_0   = 8'h20,
    ADDR_WEIGHTS_OFFSET_CTRL     = 8'h24,
    ADDR_BIAS_OFFSET_DATA_0      = 8'h28,
    ADDR_BIAS_OFFSET_CTRL        = 8'h2c,
    ADDR_IFM_CH_DATA_0           = 8'h30,
    ADDR_IFM_CH_CTRL             = 8'h34,
    ADDR_IFM_H_DATA_0            = 8'h38,
    ADDR_IFM_H_CTRL              = 8'h3c,
    ADDR_IFM_W_DATA_0            = 8'h40,
    ADDR_IFM_W_CTRL              = 8'h44,
    ADDR_OFM_CH_DATA_0           = 8'h48,
    ADDR_OFM_CH_CTRL             = 8'h4c,
    ADDR_OFM_H_DATA_0            = 8'h50,
    ADDR_OFM_H_CTRL              = 8'h54,
    ADDR_OFM_W_DATA_0            = 8'h58,
    ADDR_OFM_W_CTRL              = 8'h5c,
    ADDR_I_CH_DATA_0             = 8'h60,
    ADDR_I_CH_CTRL               = 8'h64,
    ADDR_I_H_DATA_0              = 8'h68,
    ADDR_I_H_CTRL                = 8'h6c,
    ADDR_I_W_DATA_0              = 8'h70,
    ADDR_I_W_CTRL                = 8'h74,
    ADDR_O_CH_DATA_0             = 8'h78,
    ADDR_O_CH_CTRL               = 8'h7c,
    ADDR_O_H_DATA_0              = 8'h80,
    ADDR_O_H_CTRL                = 8'h84,
    ADDR_O_W_DATA_0              = 8'h88,
    ADDR_O_W_CTRL                = 8'h8c,
    ADDR_KER_SIZE_DATA_0         = 8'h90,
    ADDR_KER_SIZE_CTRL           = 8'h94,
    ADDR_STRIDE_DATA_0           = 8'h98,
    ADDR_STRIDE_CTRL             = 8'h9c,
    ADDR_PADDING_DATA_0          = 8'ha0,
    ADDR_PADDING_CTRL            = 8'ha4,
    ADDR_LAYER_TYPE_DATA_0       = 8'ha8,
    ADDR_LAYER_TYPE_CTRL         = 8'hac,
    ADDR_ACT_SILU_DATA_0         = 8'hb0,
    ADDR_ACT_SILU_CTRL           = 8'hb4,
    ADDR_CNT_DATA_0              = 8'hb8,
    ADDR_CNT_CTRL                = 8'hbc,
    ADDR_IFM_Q1_DATA_0           = 8'hc0,
    ADDR_IFM_Q1_CTRL             = 8'hc4,
    ADDR_IFM_Q2_DATA_0           = 8'hc8,
    ADDR_IFM_Q2_CTRL             = 8'hcc,
    ADDR_WEIGHTS_Q_DATA_0        = 8'hd0,
    ADDR_WEIGHTS_Q_CTRL          = 8'hd4,
    ADDR_BIAS_Q_DATA_0           = 8'hd8,
    ADDR_BIAS_Q_CTRL             = 8'hdc,
    ADDR_OFM_Q_BEFORE_ACT_DATA_0 = 8'he0,
    ADDR_OFM_Q_BEFORE_ACT_CTRL   = 8'he4,
    ADDR_OFM_Q_AFTER_Q_DATA_0    = 8'he8,
    ADDR_OFM_Q_AFTER_Q_CTRL      = 8'hec,
    WRIDLE                       = 2'd0,
    WRDATA                       = 2'd1,
    WRRESP                       = 2'd2,
    WRRESET                      = 2'd3,
    RDIDLE                       = 2'd0,
    RDDATA                       = 2'd1,
    RDRESET                      = 2'd2,
    ADDR_BITS                = 8;

//------------------------Local signal-------------------
    reg  [1:0]                    wstate = WRRESET;
    reg  [1:0]                    wnext;
    reg  [ADDR_BITS-1:0]          waddr;
    wire [C_S_AXI_DATA_WIDTH-1:0] wmask;
    wire                          aw_hs;
    wire                          w_hs;
    reg  [1:0]                    rstate = RDRESET;
    reg  [1:0]                    rnext;
    reg  [C_S_AXI_DATA_WIDTH-1:0] rdata;
    wire                          ar_hs;
    wire [ADDR_BITS-1:0]          raddr;
    // internal registers
    reg                           int_ap_idle;
    reg                           int_ap_ready;
    reg                           int_ap_done = 1'b0;
    reg                           int_ap_start = 1'b0;
    reg                           int_auto_restart = 1'b0;
    reg                           int_gie = 1'b0;
    reg  [1:0]                    int_ier = 2'b0;
    reg  [1:0]                    int_isr = 2'b0;
    reg  [31:0]                   int_ifm_offset = 'b0;
    reg  [31:0]                   int_ofm_offset = 'b0;
    reg  [31:0]                   int_weights_offset = 'b0;
    reg  [31:0]                   int_bias_offset = 'b0;
    reg  [15:0]                   int_ifm_ch = 'b0;
    reg  [15:0]                   int_ifm_h = 'b0;
    reg  [15:0]                   int_ifm_w = 'b0;
    reg  [15:0]                   int_ofm_ch = 'b0;
    reg  [15:0]                   int_ofm_h = 'b0;
    reg  [15:0]                   int_ofm_w = 'b0;
    reg  [7:0]                    int_I_CH = 'b0;
    reg  [7:0]                    int_I_H = 'b0;
    reg  [7:0]                    int_I_W = 'b0;
    reg  [7:0]                    int_O_CH = 'b0;
    reg  [7:0]                    int_O_H = 'b0;
    reg  [7:0]                    int_O_W = 'b0;
    reg  [7:0]                    int_ker_size = 'b0;
    reg  [7:0]                    int_stride = 'b0;
    reg  [7:0]                    int_padding = 'b0;
    reg  [7:0]                    int_layer_type = 'b0;
    reg  [0:0]                    int_act_silu = 'b0;
    reg  [15:0]                   int_CNT = 'b0;
    reg  [7:0]                    int_ifm_q1 = 'b0;
    reg  [7:0]                    int_ifm_q2 = 'b0;
    reg  [7:0]                    int_weights_q = 'b0;
    reg  [7:0]                    int_bias_q = 'b0;
    reg  [7:0]                    int_ofm_q_before_act = 'b0;
    reg  [7:0]                    int_ofm_q_after_q = 'b0;

//------------------------Instantiation------------------


//------------------------AXI write fsm------------------
assign AWREADY = (wstate == WRIDLE);
assign WREADY  = (wstate == WRDATA);
assign BRESP   = 2'b00;  // OKAY
assign BVALID  = (wstate == WRRESP);
assign wmask   = { {8{WSTRB[3]}}, {8{WSTRB[2]}}, {8{WSTRB[1]}}, {8{WSTRB[0]}} };
assign aw_hs   = AWVALID & AWREADY;
assign w_hs    = WVALID & WREADY;

// wstate
always @(posedge ACLK) begin
    if (ARESET)
        wstate <= WRRESET;
    else if (ACLK_EN)
        wstate <= wnext;
end

// wnext
always @(*) begin
    case (wstate)
        WRIDLE:
            if (AWVALID)
                wnext = WRDATA;
            else
                wnext = WRIDLE;
        WRDATA:
            if (WVALID)
                wnext = WRRESP;
            else
                wnext = WRDATA;
        WRRESP:
            if (BREADY)
                wnext = WRIDLE;
            else
                wnext = WRRESP;
        default:
            wnext = WRIDLE;
    endcase
end

// waddr
always @(posedge ACLK) begin
    if (ACLK_EN) begin
        if (aw_hs)
            waddr <= AWADDR[ADDR_BITS-1:0];
    end
end

//------------------------AXI read fsm-------------------
assign ARREADY = (rstate == RDIDLE);
assign RDATA   = rdata;
assign RRESP   = 2'b00;  // OKAY
assign RVALID  = (rstate == RDDATA);
assign ar_hs   = ARVALID & ARREADY;
assign raddr   = ARADDR[ADDR_BITS-1:0];

// rstate
always @(posedge ACLK) begin
    if (ARESET)
        rstate <= RDRESET;
    else if (ACLK_EN)
        rstate <= rnext;
end

// rnext
always @(*) begin
    case (rstate)
        RDIDLE:
            if (ARVALID)
                rnext = RDDATA;
            else
                rnext = RDIDLE;
        RDDATA:
            if (RREADY & RVALID)
                rnext = RDIDLE;
            else
                rnext = RDDATA;
        default:
            rnext = RDIDLE;
    endcase
end

// rdata
always @(posedge ACLK) begin
    if (ACLK_EN) begin
        if (ar_hs) begin
            rdata <= 'b0;
            case (raddr)
                ADDR_AP_CTRL: begin
                    rdata[0] <= int_ap_start;
                    rdata[1] <= int_ap_done;
                    rdata[2] <= int_ap_idle;
                    rdata[3] <= int_ap_ready;
                    rdata[7] <= int_auto_restart;
                end
                ADDR_GIE: begin
                    rdata <= int_gie;
                end
                ADDR_IER: begin
                    rdata <= int_ier;
                end
                ADDR_ISR: begin
                    rdata <= int_isr;
                end
                ADDR_IFM_OFFSET_DATA_0: begin
                    rdata <= int_ifm_offset[31:0];
                end
                ADDR_OFM_OFFSET_DATA_0: begin
                    rdata <= int_ofm_offset[31:0];
                end
                ADDR_WEIGHTS_OFFSET_DATA_0: begin
                    rdata <= int_weights_offset[31:0];
                end
                ADDR_BIAS_OFFSET_DATA_0: begin
                    rdata <= int_bias_offset[31:0];
                end
                ADDR_IFM_CH_DATA_0: begin
                    rdata <= int_ifm_ch[15:0];
                end
                ADDR_IFM_H_DATA_0: begin
                    rdata <= int_ifm_h[15:0];
                end
                ADDR_IFM_W_DATA_0: begin
                    rdata <= int_ifm_w[15:0];
                end
                ADDR_OFM_CH_DATA_0: begin
                    rdata <= int_ofm_ch[15:0];
                end
                ADDR_OFM_H_DATA_0: begin
                    rdata <= int_ofm_h[15:0];
                end
                ADDR_OFM_W_DATA_0: begin
                    rdata <= int_ofm_w[15:0];
                end
                ADDR_I_CH_DATA_0: begin
                    rdata <= int_I_CH[7:0];
                end
                ADDR_I_H_DATA_0: begin
                    rdata <= int_I_H[7:0];
                end
                ADDR_I_W_DATA_0: begin
                    rdata <= int_I_W[7:0];
                end
                ADDR_O_CH_DATA_0: begin
                    rdata <= int_O_CH[7:0];
                end
                ADDR_O_H_DATA_0: begin
                    rdata <= int_O_H[7:0];
                end
                ADDR_O_W_DATA_0: begin
                    rdata <= int_O_W[7:0];
                end
                ADDR_KER_SIZE_DATA_0: begin
                    rdata <= int_ker_size[7:0];
                end
                ADDR_STRIDE_DATA_0: begin
                    rdata <= int_stride[7:0];
                end
                ADDR_PADDING_DATA_0: begin
                    rdata <= int_padding[7:0];
                end
                ADDR_LAYER_TYPE_DATA_0: begin
                    rdata <= int_layer_type[7:0];
                end
                ADDR_ACT_SILU_DATA_0: begin
                    rdata <= int_act_silu[0:0];
                end
                ADDR_CNT_DATA_0: begin
                    rdata <= int_CNT[15:0];
                end
                ADDR_IFM_Q1_DATA_0: begin
                    rdata <= int_ifm_q1[7:0];
                end
                ADDR_IFM_Q2_DATA_0: begin
                    rdata <= int_ifm_q2[7:0];
                end
                ADDR_WEIGHTS_Q_DATA_0: begin
                    rdata <= int_weights_q[7:0];
                end
                ADDR_BIAS_Q_DATA_0: begin
                    rdata <= int_bias_q[7:0];
                end
                ADDR_OFM_Q_BEFORE_ACT_DATA_0: begin
                    rdata <= int_ofm_q_before_act[7:0];
                end
                ADDR_OFM_Q_AFTER_Q_DATA_0: begin
                    rdata <= int_ofm_q_after_q[7:0];
                end
            endcase
        end
    end
end


//------------------------Register logic-----------------
assign interrupt        = int_gie & (|int_isr);
assign ap_start         = int_ap_start;
assign ifm_offset       = int_ifm_offset;
assign ofm_offset       = int_ofm_offset;
assign weights_offset   = int_weights_offset;
assign bias_offset      = int_bias_offset;
assign ifm_ch           = int_ifm_ch;
assign ifm_h            = int_ifm_h;
assign ifm_w            = int_ifm_w;
assign ofm_ch           = int_ofm_ch;
assign ofm_h            = int_ofm_h;
assign ofm_w            = int_ofm_w;
assign I_CH             = int_I_CH;
assign I_H              = int_I_H;
assign I_W              = int_I_W;
assign O_CH             = int_O_CH;
assign O_H              = int_O_H;
assign O_W              = int_O_W;
assign ker_size         = int_ker_size;
assign stride           = int_stride;
assign padding          = int_padding;
assign layer_type       = int_layer_type;
assign act_silu         = int_act_silu;
assign CNT              = int_CNT;
assign ifm_q1           = int_ifm_q1;
assign ifm_q2           = int_ifm_q2;
assign weights_q        = int_weights_q;
assign bias_q           = int_bias_q;
assign ofm_q_before_act = int_ofm_q_before_act;
assign ofm_q_after_q    = int_ofm_q_after_q;
// int_ap_start
always @(posedge ACLK) begin
    if (ARESET)
        int_ap_start <= 1'b0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AP_CTRL && WSTRB[0] && WDATA[0])
            int_ap_start <= 1'b1;
        else if (ap_ready)
            int_ap_start <= int_auto_restart; // clear on handshake/auto restart
    end
end

// int_ap_done
always @(posedge ACLK) begin
    if (ARESET)
        int_ap_done <= 1'b0;
    else if (ACLK_EN) begin
        if (ap_done)
            int_ap_done <= 1'b1;
        else if (ar_hs && raddr == ADDR_AP_CTRL)
            int_ap_done <= 1'b0; // clear on read
    end
end

// int_ap_idle
always @(posedge ACLK) begin
    if (ARESET)
        int_ap_idle <= 1'b0;
    else if (ACLK_EN) begin
            int_ap_idle <= ap_idle;
    end
end

// int_ap_ready
always @(posedge ACLK) begin
    if (ARESET)
        int_ap_ready <= 1'b0;
    else if (ACLK_EN) begin
            int_ap_ready <= ap_ready;
    end
end

// int_auto_restart
always @(posedge ACLK) begin
    if (ARESET)
        int_auto_restart <= 1'b0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AP_CTRL && WSTRB[0])
            int_auto_restart <=  WDATA[7];
    end
end

// int_gie
always @(posedge ACLK) begin
    if (ARESET)
        int_gie <= 1'b0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_GIE && WSTRB[0])
            int_gie <= WDATA[0];
    end
end

// int_ier
always @(posedge ACLK) begin
    if (ARESET)
        int_ier <= 1'b0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IER && WSTRB[0])
            int_ier <= WDATA[1:0];
    end
end

// int_isr[0]
always @(posedge ACLK) begin
    if (ARESET)
        int_isr[0] <= 1'b0;
    else if (ACLK_EN) begin
        if (int_ier[0] & ap_done)
            int_isr[0] <= 1'b1;
        else if (w_hs && waddr == ADDR_ISR && WSTRB[0])
            int_isr[0] <= int_isr[0] ^ WDATA[0]; // toggle on write
    end
end

// int_isr[1]
always @(posedge ACLK) begin
    if (ARESET)
        int_isr[1] <= 1'b0;
    else if (ACLK_EN) begin
        if (int_ier[1] & ap_ready)
            int_isr[1] <= 1'b1;
        else if (w_hs && waddr == ADDR_ISR && WSTRB[0])
            int_isr[1] <= int_isr[1] ^ WDATA[1]; // toggle on write
    end
end

// int_ifm_offset[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_ifm_offset[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IFM_OFFSET_DATA_0)
            int_ifm_offset[31:0] <= (WDATA[31:0] & wmask) | (int_ifm_offset[31:0] & ~wmask);
    end
end

// int_ofm_offset[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_ofm_offset[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_OFM_OFFSET_DATA_0)
            int_ofm_offset[31:0] <= (WDATA[31:0] & wmask) | (int_ofm_offset[31:0] & ~wmask);
    end
end

// int_weights_offset[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_weights_offset[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_WEIGHTS_OFFSET_DATA_0)
            int_weights_offset[31:0] <= (WDATA[31:0] & wmask) | (int_weights_offset[31:0] & ~wmask);
    end
end

// int_bias_offset[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_bias_offset[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_BIAS_OFFSET_DATA_0)
            int_bias_offset[31:0] <= (WDATA[31:0] & wmask) | (int_bias_offset[31:0] & ~wmask);
    end
end

// int_ifm_ch[15:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_ifm_ch[15:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IFM_CH_DATA_0)
            int_ifm_ch[15:0] <= (WDATA[31:0] & wmask) | (int_ifm_ch[15:0] & ~wmask);
    end
end

// int_ifm_h[15:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_ifm_h[15:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IFM_H_DATA_0)
            int_ifm_h[15:0] <= (WDATA[31:0] & wmask) | (int_ifm_h[15:0] & ~wmask);
    end
end

// int_ifm_w[15:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_ifm_w[15:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IFM_W_DATA_0)
            int_ifm_w[15:0] <= (WDATA[31:0] & wmask) | (int_ifm_w[15:0] & ~wmask);
    end
end

// int_ofm_ch[15:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_ofm_ch[15:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_OFM_CH_DATA_0)
            int_ofm_ch[15:0] <= (WDATA[31:0] & wmask) | (int_ofm_ch[15:0] & ~wmask);
    end
end

// int_ofm_h[15:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_ofm_h[15:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_OFM_H_DATA_0)
            int_ofm_h[15:0] <= (WDATA[31:0] & wmask) | (int_ofm_h[15:0] & ~wmask);
    end
end

// int_ofm_w[15:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_ofm_w[15:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_OFM_W_DATA_0)
            int_ofm_w[15:0] <= (WDATA[31:0] & wmask) | (int_ofm_w[15:0] & ~wmask);
    end
end

// int_I_CH[7:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_I_CH[7:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_I_CH_DATA_0)
            int_I_CH[7:0] <= (WDATA[31:0] & wmask) | (int_I_CH[7:0] & ~wmask);
    end
end

// int_I_H[7:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_I_H[7:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_I_H_DATA_0)
            int_I_H[7:0] <= (WDATA[31:0] & wmask) | (int_I_H[7:0] & ~wmask);
    end
end

// int_I_W[7:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_I_W[7:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_I_W_DATA_0)
            int_I_W[7:0] <= (WDATA[31:0] & wmask) | (int_I_W[7:0] & ~wmask);
    end
end

// int_O_CH[7:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_O_CH[7:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_O_CH_DATA_0)
            int_O_CH[7:0] <= (WDATA[31:0] & wmask) | (int_O_CH[7:0] & ~wmask);
    end
end

// int_O_H[7:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_O_H[7:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_O_H_DATA_0)
            int_O_H[7:0] <= (WDATA[31:0] & wmask) | (int_O_H[7:0] & ~wmask);
    end
end

// int_O_W[7:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_O_W[7:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_O_W_DATA_0)
            int_O_W[7:0] <= (WDATA[31:0] & wmask) | (int_O_W[7:0] & ~wmask);
    end
end

// int_ker_size[7:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_ker_size[7:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_KER_SIZE_DATA_0)
            int_ker_size[7:0] <= (WDATA[31:0] & wmask) | (int_ker_size[7:0] & ~wmask);
    end
end

// int_stride[7:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_stride[7:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_STRIDE_DATA_0)
            int_stride[7:0] <= (WDATA[31:0] & wmask) | (int_stride[7:0] & ~wmask);
    end
end

// int_padding[7:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_padding[7:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_PADDING_DATA_0)
            int_padding[7:0] <= (WDATA[31:0] & wmask) | (int_padding[7:0] & ~wmask);
    end
end

// int_layer_type[7:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_layer_type[7:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_LAYER_TYPE_DATA_0)
            int_layer_type[7:0] <= (WDATA[31:0] & wmask) | (int_layer_type[7:0] & ~wmask);
    end
end

// int_act_silu[0:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_act_silu[0:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_ACT_SILU_DATA_0)
            int_act_silu[0:0] <= (WDATA[31:0] & wmask) | (int_act_silu[0:0] & ~wmask);
    end
end

// int_CNT[15:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_CNT[15:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_CNT_DATA_0)
            int_CNT[15:0] <= (WDATA[31:0] & wmask) | (int_CNT[15:0] & ~wmask);
    end
end

// int_ifm_q1[7:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_ifm_q1[7:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IFM_Q1_DATA_0)
            int_ifm_q1[7:0] <= (WDATA[31:0] & wmask) | (int_ifm_q1[7:0] & ~wmask);
    end
end

// int_ifm_q2[7:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_ifm_q2[7:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IFM_Q2_DATA_0)
            int_ifm_q2[7:0] <= (WDATA[31:0] & wmask) | (int_ifm_q2[7:0] & ~wmask);
    end
end

// int_weights_q[7:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_weights_q[7:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_WEIGHTS_Q_DATA_0)
            int_weights_q[7:0] <= (WDATA[31:0] & wmask) | (int_weights_q[7:0] & ~wmask);
    end
end

// int_bias_q[7:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_bias_q[7:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_BIAS_Q_DATA_0)
            int_bias_q[7:0] <= (WDATA[31:0] & wmask) | (int_bias_q[7:0] & ~wmask);
    end
end

// int_ofm_q_before_act[7:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_ofm_q_before_act[7:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_OFM_Q_BEFORE_ACT_DATA_0)
            int_ofm_q_before_act[7:0] <= (WDATA[31:0] & wmask) | (int_ofm_q_before_act[7:0] & ~wmask);
    end
end

// int_ofm_q_after_q[7:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_ofm_q_after_q[7:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_OFM_Q_AFTER_Q_DATA_0)
            int_ofm_q_after_q[7:0] <= (WDATA[31:0] & wmask) | (int_ofm_q_after_q[7:0] & ~wmask);
    end
end


//------------------------Memory logic-------------------

endmodule
