// (c) Copyright 1995-2023 Xilinx, Inc. All rights reserved.
// 
// This file contains confidential and proprietary information
// of Xilinx, Inc. and is protected under U.S. and
// international copyright and other intellectual property
// laws.
// 
// DISCLAIMER
// This disclaimer is not a license and does not grant any
// rights to the materials distributed herewith. Except as
// otherwise provided in a valid license issued to you by
// Xilinx, and to the maximum extent permitted by applicable
// law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
// WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
// AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
// BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
// INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
// (2) Xilinx shall not be liable (whether in contract or tort,
// including negligence, or under any other theory of
// liability) for any loss or damage of any kind or nature
// related to, arising under or in connection with these
// materials, including for any direct, or any indirect,
// special, incidental, or consequential loss or damage
// (including loss of data, profits, goodwill, or any type of
// loss or damage suffered as a result of any action brought
// by a third party) even if such damage or loss was
// reasonably foreseeable or Xilinx had been advised of the
// possibility of the same.
// 
// CRITICAL APPLICATIONS
// Xilinx products are not designed or intended to be fail-
// safe, or for use in any application requiring fail-safe
// performance, such as life-support or safety devices or
// systems, Class III medical devices, nuclear facilities,
// applications related to the deployment of airbags, or any
// other applications that could lead to death, personal
// injury, or severe property or environmental damage
// (individually and collectively, "Critical
// Applications"). Customer assumes the sole risk and
// liability of any use of Xilinx products in Critical
// Applications, subject only to applicable laws and
// regulations governing limitations on product liability.
// 
// THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
// PART OF THIS FILE AT ALL TIMES.
// 
// DO NOT MODIFY THIS FILE.


// IP VLNV: xilinx.com:hls:top:1.0
// IP Revision: 2112931062

`timescale 1ns/1ps

(* IP_DEFINITION_SOURCE = "HLS" *)
(* DowngradeIPIdentifiedWarnings = "yes" *)
module top_top_0_0 (
  s_axi_ctrl_AWADDR,
  s_axi_ctrl_AWVALID,
  s_axi_ctrl_AWREADY,
  s_axi_ctrl_WDATA,
  s_axi_ctrl_WSTRB,
  s_axi_ctrl_WVALID,
  s_axi_ctrl_WREADY,
  s_axi_ctrl_BRESP,
  s_axi_ctrl_BVALID,
  s_axi_ctrl_BREADY,
  s_axi_ctrl_ARADDR,
  s_axi_ctrl_ARVALID,
  s_axi_ctrl_ARREADY,
  s_axi_ctrl_RDATA,
  s_axi_ctrl_RRESP,
  s_axi_ctrl_RVALID,
  s_axi_ctrl_RREADY,
  ap_clk,
  ap_rst_n,
  interrupt,
  m_axi_ifm_AWADDR,
  m_axi_ifm_AWLEN,
  m_axi_ifm_AWSIZE,
  m_axi_ifm_AWBURST,
  m_axi_ifm_AWLOCK,
  m_axi_ifm_AWREGION,
  m_axi_ifm_AWCACHE,
  m_axi_ifm_AWPROT,
  m_axi_ifm_AWQOS,
  m_axi_ifm_AWVALID,
  m_axi_ifm_AWREADY,
  m_axi_ifm_WDATA,
  m_axi_ifm_WSTRB,
  m_axi_ifm_WLAST,
  m_axi_ifm_WVALID,
  m_axi_ifm_WREADY,
  m_axi_ifm_BRESP,
  m_axi_ifm_BVALID,
  m_axi_ifm_BREADY,
  m_axi_ifm_ARADDR,
  m_axi_ifm_ARLEN,
  m_axi_ifm_ARSIZE,
  m_axi_ifm_ARBURST,
  m_axi_ifm_ARLOCK,
  m_axi_ifm_ARREGION,
  m_axi_ifm_ARCACHE,
  m_axi_ifm_ARPROT,
  m_axi_ifm_ARQOS,
  m_axi_ifm_ARVALID,
  m_axi_ifm_ARREADY,
  m_axi_ifm_RDATA,
  m_axi_ifm_RRESP,
  m_axi_ifm_RLAST,
  m_axi_ifm_RVALID,
  m_axi_ifm_RREADY,
  m_axi_ofm_AWADDR,
  m_axi_ofm_AWLEN,
  m_axi_ofm_AWSIZE,
  m_axi_ofm_AWBURST,
  m_axi_ofm_AWLOCK,
  m_axi_ofm_AWREGION,
  m_axi_ofm_AWCACHE,
  m_axi_ofm_AWPROT,
  m_axi_ofm_AWQOS,
  m_axi_ofm_AWVALID,
  m_axi_ofm_AWREADY,
  m_axi_ofm_WDATA,
  m_axi_ofm_WSTRB,
  m_axi_ofm_WLAST,
  m_axi_ofm_WVALID,
  m_axi_ofm_WREADY,
  m_axi_ofm_BRESP,
  m_axi_ofm_BVALID,
  m_axi_ofm_BREADY,
  m_axi_ofm_ARADDR,
  m_axi_ofm_ARLEN,
  m_axi_ofm_ARSIZE,
  m_axi_ofm_ARBURST,
  m_axi_ofm_ARLOCK,
  m_axi_ofm_ARREGION,
  m_axi_ofm_ARCACHE,
  m_axi_ofm_ARPROT,
  m_axi_ofm_ARQOS,
  m_axi_ofm_ARVALID,
  m_axi_ofm_ARREADY,
  m_axi_ofm_RDATA,
  m_axi_ofm_RRESP,
  m_axi_ofm_RLAST,
  m_axi_ofm_RVALID,
  m_axi_ofm_RREADY,
  m_axi_weights_AWADDR,
  m_axi_weights_AWLEN,
  m_axi_weights_AWSIZE,
  m_axi_weights_AWBURST,
  m_axi_weights_AWLOCK,
  m_axi_weights_AWREGION,
  m_axi_weights_AWCACHE,
  m_axi_weights_AWPROT,
  m_axi_weights_AWQOS,
  m_axi_weights_AWVALID,
  m_axi_weights_AWREADY,
  m_axi_weights_WDATA,
  m_axi_weights_WSTRB,
  m_axi_weights_WLAST,
  m_axi_weights_WVALID,
  m_axi_weights_WREADY,
  m_axi_weights_BRESP,
  m_axi_weights_BVALID,
  m_axi_weights_BREADY,
  m_axi_weights_ARADDR,
  m_axi_weights_ARLEN,
  m_axi_weights_ARSIZE,
  m_axi_weights_ARBURST,
  m_axi_weights_ARLOCK,
  m_axi_weights_ARREGION,
  m_axi_weights_ARCACHE,
  m_axi_weights_ARPROT,
  m_axi_weights_ARQOS,
  m_axi_weights_ARVALID,
  m_axi_weights_ARREADY,
  m_axi_weights_RDATA,
  m_axi_weights_RRESP,
  m_axi_weights_RLAST,
  m_axi_weights_RVALID,
  m_axi_weights_RREADY,
  m_axi_bias_AWADDR,
  m_axi_bias_AWLEN,
  m_axi_bias_AWSIZE,
  m_axi_bias_AWBURST,
  m_axi_bias_AWLOCK,
  m_axi_bias_AWREGION,
  m_axi_bias_AWCACHE,
  m_axi_bias_AWPROT,
  m_axi_bias_AWQOS,
  m_axi_bias_AWVALID,
  m_axi_bias_AWREADY,
  m_axi_bias_WDATA,
  m_axi_bias_WSTRB,
  m_axi_bias_WLAST,
  m_axi_bias_WVALID,
  m_axi_bias_WREADY,
  m_axi_bias_BRESP,
  m_axi_bias_BVALID,
  m_axi_bias_BREADY,
  m_axi_bias_ARADDR,
  m_axi_bias_ARLEN,
  m_axi_bias_ARSIZE,
  m_axi_bias_ARBURST,
  m_axi_bias_ARLOCK,
  m_axi_bias_ARREGION,
  m_axi_bias_ARCACHE,
  m_axi_bias_ARPROT,
  m_axi_bias_ARQOS,
  m_axi_bias_ARVALID,
  m_axi_bias_ARREADY,
  m_axi_bias_RDATA,
  m_axi_bias_RRESP,
  m_axi_bias_RLAST,
  m_axi_bias_RVALID,
  m_axi_bias_RREADY
);

(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_ctrl AWADDR" *)
input wire [7 : 0] s_axi_ctrl_AWADDR;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_ctrl AWVALID" *)
input wire s_axi_ctrl_AWVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_ctrl AWREADY" *)
output wire s_axi_ctrl_AWREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_ctrl WDATA" *)
input wire [31 : 0] s_axi_ctrl_WDATA;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_ctrl WSTRB" *)
input wire [3 : 0] s_axi_ctrl_WSTRB;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_ctrl WVALID" *)
input wire s_axi_ctrl_WVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_ctrl WREADY" *)
output wire s_axi_ctrl_WREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_ctrl BRESP" *)
output wire [1 : 0] s_axi_ctrl_BRESP;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_ctrl BVALID" *)
output wire s_axi_ctrl_BVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_ctrl BREADY" *)
input wire s_axi_ctrl_BREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_ctrl ARADDR" *)
input wire [7 : 0] s_axi_ctrl_ARADDR;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_ctrl ARVALID" *)
input wire s_axi_ctrl_ARVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_ctrl ARREADY" *)
output wire s_axi_ctrl_ARREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_ctrl RDATA" *)
output wire [31 : 0] s_axi_ctrl_RDATA;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_ctrl RRESP" *)
output wire [1 : 0] s_axi_ctrl_RRESP;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_ctrl RVALID" *)
output wire s_axi_ctrl_RVALID;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME s_axi_ctrl, ADDR_WIDTH 8, DATA_WIDTH 32, PROTOCOL AXI4LITE, READ_WRITE_MODE READ_WRITE, FREQ_HZ 100000000, ID_WIDTH 0, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, HAS_BURST 0, HAS_LOCK 0, HAS_PROT 0, HAS_CACHE 0, HAS_QOS 0, HAS_REGION 0, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, SUPPORTS_NARROW_BURST 0, NUM_READ_OUTSTANDING 1, NUM_WRITE_OUTSTANDING 1, MAX_BURST_LENGTH 1, PHASE 0.0, CLK_DOMAIN /clk_wiz_0_clk_out1, NUM_READ_THREADS 4, NUM_WRITE_THREA\
DS 4, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_ctrl RREADY" *)
input wire s_axi_ctrl_RREADY;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME ap_clk, ASSOCIATED_BUSIF s_axi_ctrl:m_axi_ifm:m_axi_ofm:m_axi_weights:m_axi_bias, ASSOCIATED_RESET ap_rst_n, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, PHASE 0.0, CLK_DOMAIN /clk_wiz_0_clk_out1, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 ap_clk CLK" *)
input wire ap_clk;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME ap_rst_n, POLARITY ACTIVE_LOW, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 ap_rst_n RST" *)
input wire ap_rst_n;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME interrupt, SENSITIVITY LEVEL_HIGH, PortWidth 1" *)
(* X_INTERFACE_INFO = "xilinx.com:signal:interrupt:1.0 interrupt INTERRUPT" *)
output wire interrupt;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ifm AWADDR" *)
output wire [31 : 0] m_axi_ifm_AWADDR;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ifm AWLEN" *)
output wire [7 : 0] m_axi_ifm_AWLEN;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ifm AWSIZE" *)
output wire [2 : 0] m_axi_ifm_AWSIZE;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ifm AWBURST" *)
output wire [1 : 0] m_axi_ifm_AWBURST;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ifm AWLOCK" *)
output wire [1 : 0] m_axi_ifm_AWLOCK;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ifm AWREGION" *)
output wire [3 : 0] m_axi_ifm_AWREGION;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ifm AWCACHE" *)
output wire [3 : 0] m_axi_ifm_AWCACHE;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ifm AWPROT" *)
output wire [2 : 0] m_axi_ifm_AWPROT;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ifm AWQOS" *)
output wire [3 : 0] m_axi_ifm_AWQOS;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ifm AWVALID" *)
output wire m_axi_ifm_AWVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ifm AWREADY" *)
input wire m_axi_ifm_AWREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ifm WDATA" *)
output wire [31 : 0] m_axi_ifm_WDATA;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ifm WSTRB" *)
output wire [3 : 0] m_axi_ifm_WSTRB;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ifm WLAST" *)
output wire m_axi_ifm_WLAST;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ifm WVALID" *)
output wire m_axi_ifm_WVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ifm WREADY" *)
input wire m_axi_ifm_WREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ifm BRESP" *)
input wire [1 : 0] m_axi_ifm_BRESP;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ifm BVALID" *)
input wire m_axi_ifm_BVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ifm BREADY" *)
output wire m_axi_ifm_BREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ifm ARADDR" *)
output wire [31 : 0] m_axi_ifm_ARADDR;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ifm ARLEN" *)
output wire [7 : 0] m_axi_ifm_ARLEN;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ifm ARSIZE" *)
output wire [2 : 0] m_axi_ifm_ARSIZE;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ifm ARBURST" *)
output wire [1 : 0] m_axi_ifm_ARBURST;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ifm ARLOCK" *)
output wire [1 : 0] m_axi_ifm_ARLOCK;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ifm ARREGION" *)
output wire [3 : 0] m_axi_ifm_ARREGION;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ifm ARCACHE" *)
output wire [3 : 0] m_axi_ifm_ARCACHE;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ifm ARPROT" *)
output wire [2 : 0] m_axi_ifm_ARPROT;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ifm ARQOS" *)
output wire [3 : 0] m_axi_ifm_ARQOS;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ifm ARVALID" *)
output wire m_axi_ifm_ARVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ifm ARREADY" *)
input wire m_axi_ifm_ARREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ifm RDATA" *)
input wire [31 : 0] m_axi_ifm_RDATA;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ifm RRESP" *)
input wire [1 : 0] m_axi_ifm_RRESP;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ifm RLAST" *)
input wire m_axi_ifm_RLAST;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ifm RVALID" *)
input wire m_axi_ifm_RVALID;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME m_axi_ifm, ADDR_WIDTH 32, MAX_BURST_LENGTH 256, NUM_READ_OUTSTANDING 2, NUM_WRITE_OUTSTANDING 2, MAX_READ_BURST_LENGTH 128, MAX_WRITE_BURST_LENGTH 128, PROTOCOL AXI4, READ_WRITE_MODE READ_WRITE, HAS_BURST 0, SUPPORTS_NARROW_BURST 0, DATA_WIDTH 32, FREQ_HZ 100000000, ID_WIDTH 0, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, HAS_LOCK 1, HAS_PROT 1, HAS_CACHE 1, HAS_QOS 1, HAS_REGION 1, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, PHASE 0.0, CLK_DOMAIN /cl\
k_wiz_0_clk_out1, NUM_READ_THREADS 1, NUM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ifm RREADY" *)
output wire m_axi_ifm_RREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ofm AWADDR" *)
output wire [31 : 0] m_axi_ofm_AWADDR;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ofm AWLEN" *)
output wire [7 : 0] m_axi_ofm_AWLEN;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ofm AWSIZE" *)
output wire [2 : 0] m_axi_ofm_AWSIZE;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ofm AWBURST" *)
output wire [1 : 0] m_axi_ofm_AWBURST;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ofm AWLOCK" *)
output wire [1 : 0] m_axi_ofm_AWLOCK;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ofm AWREGION" *)
output wire [3 : 0] m_axi_ofm_AWREGION;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ofm AWCACHE" *)
output wire [3 : 0] m_axi_ofm_AWCACHE;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ofm AWPROT" *)
output wire [2 : 0] m_axi_ofm_AWPROT;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ofm AWQOS" *)
output wire [3 : 0] m_axi_ofm_AWQOS;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ofm AWVALID" *)
output wire m_axi_ofm_AWVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ofm AWREADY" *)
input wire m_axi_ofm_AWREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ofm WDATA" *)
output wire [31 : 0] m_axi_ofm_WDATA;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ofm WSTRB" *)
output wire [3 : 0] m_axi_ofm_WSTRB;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ofm WLAST" *)
output wire m_axi_ofm_WLAST;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ofm WVALID" *)
output wire m_axi_ofm_WVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ofm WREADY" *)
input wire m_axi_ofm_WREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ofm BRESP" *)
input wire [1 : 0] m_axi_ofm_BRESP;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ofm BVALID" *)
input wire m_axi_ofm_BVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ofm BREADY" *)
output wire m_axi_ofm_BREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ofm ARADDR" *)
output wire [31 : 0] m_axi_ofm_ARADDR;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ofm ARLEN" *)
output wire [7 : 0] m_axi_ofm_ARLEN;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ofm ARSIZE" *)
output wire [2 : 0] m_axi_ofm_ARSIZE;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ofm ARBURST" *)
output wire [1 : 0] m_axi_ofm_ARBURST;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ofm ARLOCK" *)
output wire [1 : 0] m_axi_ofm_ARLOCK;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ofm ARREGION" *)
output wire [3 : 0] m_axi_ofm_ARREGION;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ofm ARCACHE" *)
output wire [3 : 0] m_axi_ofm_ARCACHE;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ofm ARPROT" *)
output wire [2 : 0] m_axi_ofm_ARPROT;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ofm ARQOS" *)
output wire [3 : 0] m_axi_ofm_ARQOS;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ofm ARVALID" *)
output wire m_axi_ofm_ARVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ofm ARREADY" *)
input wire m_axi_ofm_ARREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ofm RDATA" *)
input wire [31 : 0] m_axi_ofm_RDATA;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ofm RRESP" *)
input wire [1 : 0] m_axi_ofm_RRESP;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ofm RLAST" *)
input wire m_axi_ofm_RLAST;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ofm RVALID" *)
input wire m_axi_ofm_RVALID;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME m_axi_ofm, ADDR_WIDTH 32, MAX_BURST_LENGTH 256, NUM_READ_OUTSTANDING 2, NUM_WRITE_OUTSTANDING 2, MAX_READ_BURST_LENGTH 128, MAX_WRITE_BURST_LENGTH 128, PROTOCOL AXI4, READ_WRITE_MODE READ_WRITE, HAS_BURST 0, SUPPORTS_NARROW_BURST 0, DATA_WIDTH 32, FREQ_HZ 100000000, ID_WIDTH 0, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, HAS_LOCK 1, HAS_PROT 1, HAS_CACHE 1, HAS_QOS 1, HAS_REGION 1, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, PHASE 0.0, CLK_DOMAIN /cl\
k_wiz_0_clk_out1, NUM_READ_THREADS 1, NUM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_ofm RREADY" *)
output wire m_axi_ofm_RREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_weights AWADDR" *)
output wire [31 : 0] m_axi_weights_AWADDR;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_weights AWLEN" *)
output wire [7 : 0] m_axi_weights_AWLEN;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_weights AWSIZE" *)
output wire [2 : 0] m_axi_weights_AWSIZE;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_weights AWBURST" *)
output wire [1 : 0] m_axi_weights_AWBURST;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_weights AWLOCK" *)
output wire [1 : 0] m_axi_weights_AWLOCK;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_weights AWREGION" *)
output wire [3 : 0] m_axi_weights_AWREGION;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_weights AWCACHE" *)
output wire [3 : 0] m_axi_weights_AWCACHE;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_weights AWPROT" *)
output wire [2 : 0] m_axi_weights_AWPROT;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_weights AWQOS" *)
output wire [3 : 0] m_axi_weights_AWQOS;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_weights AWVALID" *)
output wire m_axi_weights_AWVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_weights AWREADY" *)
input wire m_axi_weights_AWREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_weights WDATA" *)
output wire [31 : 0] m_axi_weights_WDATA;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_weights WSTRB" *)
output wire [3 : 0] m_axi_weights_WSTRB;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_weights WLAST" *)
output wire m_axi_weights_WLAST;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_weights WVALID" *)
output wire m_axi_weights_WVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_weights WREADY" *)
input wire m_axi_weights_WREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_weights BRESP" *)
input wire [1 : 0] m_axi_weights_BRESP;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_weights BVALID" *)
input wire m_axi_weights_BVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_weights BREADY" *)
output wire m_axi_weights_BREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_weights ARADDR" *)
output wire [31 : 0] m_axi_weights_ARADDR;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_weights ARLEN" *)
output wire [7 : 0] m_axi_weights_ARLEN;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_weights ARSIZE" *)
output wire [2 : 0] m_axi_weights_ARSIZE;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_weights ARBURST" *)
output wire [1 : 0] m_axi_weights_ARBURST;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_weights ARLOCK" *)
output wire [1 : 0] m_axi_weights_ARLOCK;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_weights ARREGION" *)
output wire [3 : 0] m_axi_weights_ARREGION;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_weights ARCACHE" *)
output wire [3 : 0] m_axi_weights_ARCACHE;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_weights ARPROT" *)
output wire [2 : 0] m_axi_weights_ARPROT;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_weights ARQOS" *)
output wire [3 : 0] m_axi_weights_ARQOS;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_weights ARVALID" *)
output wire m_axi_weights_ARVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_weights ARREADY" *)
input wire m_axi_weights_ARREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_weights RDATA" *)
input wire [31 : 0] m_axi_weights_RDATA;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_weights RRESP" *)
input wire [1 : 0] m_axi_weights_RRESP;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_weights RLAST" *)
input wire m_axi_weights_RLAST;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_weights RVALID" *)
input wire m_axi_weights_RVALID;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME m_axi_weights, ADDR_WIDTH 32, MAX_BURST_LENGTH 256, NUM_READ_OUTSTANDING 2, NUM_WRITE_OUTSTANDING 2, MAX_READ_BURST_LENGTH 256, MAX_WRITE_BURST_LENGTH 256, PROTOCOL AXI4, READ_WRITE_MODE READ_WRITE, HAS_BURST 0, SUPPORTS_NARROW_BURST 0, DATA_WIDTH 32, FREQ_HZ 100000000, ID_WIDTH 0, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, HAS_LOCK 1, HAS_PROT 1, HAS_CACHE 1, HAS_QOS 1, HAS_REGION 1, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, PHASE 0.0, CLK_DOMAIN\
 /clk_wiz_0_clk_out1, NUM_READ_THREADS 1, NUM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_weights RREADY" *)
output wire m_axi_weights_RREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_bias AWADDR" *)
output wire [31 : 0] m_axi_bias_AWADDR;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_bias AWLEN" *)
output wire [7 : 0] m_axi_bias_AWLEN;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_bias AWSIZE" *)
output wire [2 : 0] m_axi_bias_AWSIZE;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_bias AWBURST" *)
output wire [1 : 0] m_axi_bias_AWBURST;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_bias AWLOCK" *)
output wire [1 : 0] m_axi_bias_AWLOCK;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_bias AWREGION" *)
output wire [3 : 0] m_axi_bias_AWREGION;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_bias AWCACHE" *)
output wire [3 : 0] m_axi_bias_AWCACHE;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_bias AWPROT" *)
output wire [2 : 0] m_axi_bias_AWPROT;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_bias AWQOS" *)
output wire [3 : 0] m_axi_bias_AWQOS;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_bias AWVALID" *)
output wire m_axi_bias_AWVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_bias AWREADY" *)
input wire m_axi_bias_AWREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_bias WDATA" *)
output wire [31 : 0] m_axi_bias_WDATA;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_bias WSTRB" *)
output wire [3 : 0] m_axi_bias_WSTRB;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_bias WLAST" *)
output wire m_axi_bias_WLAST;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_bias WVALID" *)
output wire m_axi_bias_WVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_bias WREADY" *)
input wire m_axi_bias_WREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_bias BRESP" *)
input wire [1 : 0] m_axi_bias_BRESP;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_bias BVALID" *)
input wire m_axi_bias_BVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_bias BREADY" *)
output wire m_axi_bias_BREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_bias ARADDR" *)
output wire [31 : 0] m_axi_bias_ARADDR;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_bias ARLEN" *)
output wire [7 : 0] m_axi_bias_ARLEN;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_bias ARSIZE" *)
output wire [2 : 0] m_axi_bias_ARSIZE;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_bias ARBURST" *)
output wire [1 : 0] m_axi_bias_ARBURST;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_bias ARLOCK" *)
output wire [1 : 0] m_axi_bias_ARLOCK;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_bias ARREGION" *)
output wire [3 : 0] m_axi_bias_ARREGION;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_bias ARCACHE" *)
output wire [3 : 0] m_axi_bias_ARCACHE;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_bias ARPROT" *)
output wire [2 : 0] m_axi_bias_ARPROT;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_bias ARQOS" *)
output wire [3 : 0] m_axi_bias_ARQOS;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_bias ARVALID" *)
output wire m_axi_bias_ARVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_bias ARREADY" *)
input wire m_axi_bias_ARREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_bias RDATA" *)
input wire [31 : 0] m_axi_bias_RDATA;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_bias RRESP" *)
input wire [1 : 0] m_axi_bias_RRESP;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_bias RLAST" *)
input wire m_axi_bias_RLAST;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_bias RVALID" *)
input wire m_axi_bias_RVALID;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME m_axi_bias, ADDR_WIDTH 32, MAX_BURST_LENGTH 256, NUM_READ_OUTSTANDING 2, NUM_WRITE_OUTSTANDING 2, MAX_READ_BURST_LENGTH 256, MAX_WRITE_BURST_LENGTH 256, PROTOCOL AXI4, READ_WRITE_MODE READ_WRITE, HAS_BURST 0, SUPPORTS_NARROW_BURST 0, DATA_WIDTH 32, FREQ_HZ 100000000, ID_WIDTH 0, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, HAS_LOCK 1, HAS_PROT 1, HAS_CACHE 1, HAS_QOS 1, HAS_REGION 1, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, PHASE 0.0, CLK_DOMAIN /c\
lk_wiz_0_clk_out1, NUM_READ_THREADS 1, NUM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_bias RREADY" *)
output wire m_axi_bias_RREADY;

(* SDX_KERNEL = "true" *)
(* SDX_KERNEL_TYPE = "hls" *)
(* SDX_KERNEL_SIM_INST = "" *)
  top #(
    .C_S_AXI_CTRL_ADDR_WIDTH(8),
    .C_S_AXI_CTRL_DATA_WIDTH(32),
    .C_M_AXI_IFM_ID_WIDTH(1),
    .C_M_AXI_IFM_ADDR_WIDTH(32),
    .C_M_AXI_IFM_DATA_WIDTH(32),
    .C_M_AXI_IFM_AWUSER_WIDTH(1),
    .C_M_AXI_IFM_ARUSER_WIDTH(1),
    .C_M_AXI_IFM_WUSER_WIDTH(1),
    .C_M_AXI_IFM_RUSER_WIDTH(1),
    .C_M_AXI_IFM_BUSER_WIDTH(1),
    .C_M_AXI_IFM_USER_VALUE(32'H00000000),
    .C_M_AXI_IFM_PROT_VALUE(3'B000),
    .C_M_AXI_IFM_CACHE_VALUE(4'B0011),
    .C_M_AXI_OFM_ID_WIDTH(1),
    .C_M_AXI_OFM_ADDR_WIDTH(32),
    .C_M_AXI_OFM_DATA_WIDTH(32),
    .C_M_AXI_OFM_AWUSER_WIDTH(1),
    .C_M_AXI_OFM_ARUSER_WIDTH(1),
    .C_M_AXI_OFM_WUSER_WIDTH(1),
    .C_M_AXI_OFM_RUSER_WIDTH(1),
    .C_M_AXI_OFM_BUSER_WIDTH(1),
    .C_M_AXI_OFM_USER_VALUE(32'H00000000),
    .C_M_AXI_OFM_PROT_VALUE(3'B000),
    .C_M_AXI_OFM_CACHE_VALUE(4'B0011),
    .C_M_AXI_WEIGHTS_ID_WIDTH(1),
    .C_M_AXI_WEIGHTS_ADDR_WIDTH(32),
    .C_M_AXI_WEIGHTS_DATA_WIDTH(32),
    .C_M_AXI_WEIGHTS_AWUSER_WIDTH(1),
    .C_M_AXI_WEIGHTS_ARUSER_WIDTH(1),
    .C_M_AXI_WEIGHTS_WUSER_WIDTH(1),
    .C_M_AXI_WEIGHTS_RUSER_WIDTH(1),
    .C_M_AXI_WEIGHTS_BUSER_WIDTH(1),
    .C_M_AXI_WEIGHTS_USER_VALUE(32'H00000000),
    .C_M_AXI_WEIGHTS_PROT_VALUE(3'B000),
    .C_M_AXI_WEIGHTS_CACHE_VALUE(4'B0011),
    .C_M_AXI_BIAS_ID_WIDTH(1),
    .C_M_AXI_BIAS_ADDR_WIDTH(32),
    .C_M_AXI_BIAS_DATA_WIDTH(32),
    .C_M_AXI_BIAS_AWUSER_WIDTH(1),
    .C_M_AXI_BIAS_ARUSER_WIDTH(1),
    .C_M_AXI_BIAS_WUSER_WIDTH(1),
    .C_M_AXI_BIAS_RUSER_WIDTH(1),
    .C_M_AXI_BIAS_BUSER_WIDTH(1),
    .C_M_AXI_BIAS_USER_VALUE(32'H00000000),
    .C_M_AXI_BIAS_PROT_VALUE(3'B000),
    .C_M_AXI_BIAS_CACHE_VALUE(4'B0011)
  ) inst (
    .s_axi_ctrl_AWADDR(s_axi_ctrl_AWADDR),
    .s_axi_ctrl_AWVALID(s_axi_ctrl_AWVALID),
    .s_axi_ctrl_AWREADY(s_axi_ctrl_AWREADY),
    .s_axi_ctrl_WDATA(s_axi_ctrl_WDATA),
    .s_axi_ctrl_WSTRB(s_axi_ctrl_WSTRB),
    .s_axi_ctrl_WVALID(s_axi_ctrl_WVALID),
    .s_axi_ctrl_WREADY(s_axi_ctrl_WREADY),
    .s_axi_ctrl_BRESP(s_axi_ctrl_BRESP),
    .s_axi_ctrl_BVALID(s_axi_ctrl_BVALID),
    .s_axi_ctrl_BREADY(s_axi_ctrl_BREADY),
    .s_axi_ctrl_ARADDR(s_axi_ctrl_ARADDR),
    .s_axi_ctrl_ARVALID(s_axi_ctrl_ARVALID),
    .s_axi_ctrl_ARREADY(s_axi_ctrl_ARREADY),
    .s_axi_ctrl_RDATA(s_axi_ctrl_RDATA),
    .s_axi_ctrl_RRESP(s_axi_ctrl_RRESP),
    .s_axi_ctrl_RVALID(s_axi_ctrl_RVALID),
    .s_axi_ctrl_RREADY(s_axi_ctrl_RREADY),
    .ap_clk(ap_clk),
    .ap_rst_n(ap_rst_n),
    .interrupt(interrupt),
    .m_axi_ifm_AWID(),
    .m_axi_ifm_AWADDR(m_axi_ifm_AWADDR),
    .m_axi_ifm_AWLEN(m_axi_ifm_AWLEN),
    .m_axi_ifm_AWSIZE(m_axi_ifm_AWSIZE),
    .m_axi_ifm_AWBURST(m_axi_ifm_AWBURST),
    .m_axi_ifm_AWLOCK(m_axi_ifm_AWLOCK),
    .m_axi_ifm_AWREGION(m_axi_ifm_AWREGION),
    .m_axi_ifm_AWCACHE(m_axi_ifm_AWCACHE),
    .m_axi_ifm_AWPROT(m_axi_ifm_AWPROT),
    .m_axi_ifm_AWQOS(m_axi_ifm_AWQOS),
    .m_axi_ifm_AWUSER(),
    .m_axi_ifm_AWVALID(m_axi_ifm_AWVALID),
    .m_axi_ifm_AWREADY(m_axi_ifm_AWREADY),
    .m_axi_ifm_WID(),
    .m_axi_ifm_WDATA(m_axi_ifm_WDATA),
    .m_axi_ifm_WSTRB(m_axi_ifm_WSTRB),
    .m_axi_ifm_WLAST(m_axi_ifm_WLAST),
    .m_axi_ifm_WUSER(),
    .m_axi_ifm_WVALID(m_axi_ifm_WVALID),
    .m_axi_ifm_WREADY(m_axi_ifm_WREADY),
    .m_axi_ifm_BID(1'B0),
    .m_axi_ifm_BRESP(m_axi_ifm_BRESP),
    .m_axi_ifm_BUSER(1'B0),
    .m_axi_ifm_BVALID(m_axi_ifm_BVALID),
    .m_axi_ifm_BREADY(m_axi_ifm_BREADY),
    .m_axi_ifm_ARID(),
    .m_axi_ifm_ARADDR(m_axi_ifm_ARADDR),
    .m_axi_ifm_ARLEN(m_axi_ifm_ARLEN),
    .m_axi_ifm_ARSIZE(m_axi_ifm_ARSIZE),
    .m_axi_ifm_ARBURST(m_axi_ifm_ARBURST),
    .m_axi_ifm_ARLOCK(m_axi_ifm_ARLOCK),
    .m_axi_ifm_ARREGION(m_axi_ifm_ARREGION),
    .m_axi_ifm_ARCACHE(m_axi_ifm_ARCACHE),
    .m_axi_ifm_ARPROT(m_axi_ifm_ARPROT),
    .m_axi_ifm_ARQOS(m_axi_ifm_ARQOS),
    .m_axi_ifm_ARUSER(),
    .m_axi_ifm_ARVALID(m_axi_ifm_ARVALID),
    .m_axi_ifm_ARREADY(m_axi_ifm_ARREADY),
    .m_axi_ifm_RID(1'B0),
    .m_axi_ifm_RDATA(m_axi_ifm_RDATA),
    .m_axi_ifm_RRESP(m_axi_ifm_RRESP),
    .m_axi_ifm_RLAST(m_axi_ifm_RLAST),
    .m_axi_ifm_RUSER(1'B0),
    .m_axi_ifm_RVALID(m_axi_ifm_RVALID),
    .m_axi_ifm_RREADY(m_axi_ifm_RREADY),
    .m_axi_ofm_AWID(),
    .m_axi_ofm_AWADDR(m_axi_ofm_AWADDR),
    .m_axi_ofm_AWLEN(m_axi_ofm_AWLEN),
    .m_axi_ofm_AWSIZE(m_axi_ofm_AWSIZE),
    .m_axi_ofm_AWBURST(m_axi_ofm_AWBURST),
    .m_axi_ofm_AWLOCK(m_axi_ofm_AWLOCK),
    .m_axi_ofm_AWREGION(m_axi_ofm_AWREGION),
    .m_axi_ofm_AWCACHE(m_axi_ofm_AWCACHE),
    .m_axi_ofm_AWPROT(m_axi_ofm_AWPROT),
    .m_axi_ofm_AWQOS(m_axi_ofm_AWQOS),
    .m_axi_ofm_AWUSER(),
    .m_axi_ofm_AWVALID(m_axi_ofm_AWVALID),
    .m_axi_ofm_AWREADY(m_axi_ofm_AWREADY),
    .m_axi_ofm_WID(),
    .m_axi_ofm_WDATA(m_axi_ofm_WDATA),
    .m_axi_ofm_WSTRB(m_axi_ofm_WSTRB),
    .m_axi_ofm_WLAST(m_axi_ofm_WLAST),
    .m_axi_ofm_WUSER(),
    .m_axi_ofm_WVALID(m_axi_ofm_WVALID),
    .m_axi_ofm_WREADY(m_axi_ofm_WREADY),
    .m_axi_ofm_BID(1'B0),
    .m_axi_ofm_BRESP(m_axi_ofm_BRESP),
    .m_axi_ofm_BUSER(1'B0),
    .m_axi_ofm_BVALID(m_axi_ofm_BVALID),
    .m_axi_ofm_BREADY(m_axi_ofm_BREADY),
    .m_axi_ofm_ARID(),
    .m_axi_ofm_ARADDR(m_axi_ofm_ARADDR),
    .m_axi_ofm_ARLEN(m_axi_ofm_ARLEN),
    .m_axi_ofm_ARSIZE(m_axi_ofm_ARSIZE),
    .m_axi_ofm_ARBURST(m_axi_ofm_ARBURST),
    .m_axi_ofm_ARLOCK(m_axi_ofm_ARLOCK),
    .m_axi_ofm_ARREGION(m_axi_ofm_ARREGION),
    .m_axi_ofm_ARCACHE(m_axi_ofm_ARCACHE),
    .m_axi_ofm_ARPROT(m_axi_ofm_ARPROT),
    .m_axi_ofm_ARQOS(m_axi_ofm_ARQOS),
    .m_axi_ofm_ARUSER(),
    .m_axi_ofm_ARVALID(m_axi_ofm_ARVALID),
    .m_axi_ofm_ARREADY(m_axi_ofm_ARREADY),
    .m_axi_ofm_RID(1'B0),
    .m_axi_ofm_RDATA(m_axi_ofm_RDATA),
    .m_axi_ofm_RRESP(m_axi_ofm_RRESP),
    .m_axi_ofm_RLAST(m_axi_ofm_RLAST),
    .m_axi_ofm_RUSER(1'B0),
    .m_axi_ofm_RVALID(m_axi_ofm_RVALID),
    .m_axi_ofm_RREADY(m_axi_ofm_RREADY),
    .m_axi_weights_AWID(),
    .m_axi_weights_AWADDR(m_axi_weights_AWADDR),
    .m_axi_weights_AWLEN(m_axi_weights_AWLEN),
    .m_axi_weights_AWSIZE(m_axi_weights_AWSIZE),
    .m_axi_weights_AWBURST(m_axi_weights_AWBURST),
    .m_axi_weights_AWLOCK(m_axi_weights_AWLOCK),
    .m_axi_weights_AWREGION(m_axi_weights_AWREGION),
    .m_axi_weights_AWCACHE(m_axi_weights_AWCACHE),
    .m_axi_weights_AWPROT(m_axi_weights_AWPROT),
    .m_axi_weights_AWQOS(m_axi_weights_AWQOS),
    .m_axi_weights_AWUSER(),
    .m_axi_weights_AWVALID(m_axi_weights_AWVALID),
    .m_axi_weights_AWREADY(m_axi_weights_AWREADY),
    .m_axi_weights_WID(),
    .m_axi_weights_WDATA(m_axi_weights_WDATA),
    .m_axi_weights_WSTRB(m_axi_weights_WSTRB),
    .m_axi_weights_WLAST(m_axi_weights_WLAST),
    .m_axi_weights_WUSER(),
    .m_axi_weights_WVALID(m_axi_weights_WVALID),
    .m_axi_weights_WREADY(m_axi_weights_WREADY),
    .m_axi_weights_BID(1'B0),
    .m_axi_weights_BRESP(m_axi_weights_BRESP),
    .m_axi_weights_BUSER(1'B0),
    .m_axi_weights_BVALID(m_axi_weights_BVALID),
    .m_axi_weights_BREADY(m_axi_weights_BREADY),
    .m_axi_weights_ARID(),
    .m_axi_weights_ARADDR(m_axi_weights_ARADDR),
    .m_axi_weights_ARLEN(m_axi_weights_ARLEN),
    .m_axi_weights_ARSIZE(m_axi_weights_ARSIZE),
    .m_axi_weights_ARBURST(m_axi_weights_ARBURST),
    .m_axi_weights_ARLOCK(m_axi_weights_ARLOCK),
    .m_axi_weights_ARREGION(m_axi_weights_ARREGION),
    .m_axi_weights_ARCACHE(m_axi_weights_ARCACHE),
    .m_axi_weights_ARPROT(m_axi_weights_ARPROT),
    .m_axi_weights_ARQOS(m_axi_weights_ARQOS),
    .m_axi_weights_ARUSER(),
    .m_axi_weights_ARVALID(m_axi_weights_ARVALID),
    .m_axi_weights_ARREADY(m_axi_weights_ARREADY),
    .m_axi_weights_RID(1'B0),
    .m_axi_weights_RDATA(m_axi_weights_RDATA),
    .m_axi_weights_RRESP(m_axi_weights_RRESP),
    .m_axi_weights_RLAST(m_axi_weights_RLAST),
    .m_axi_weights_RUSER(1'B0),
    .m_axi_weights_RVALID(m_axi_weights_RVALID),
    .m_axi_weights_RREADY(m_axi_weights_RREADY),
    .m_axi_bias_AWID(),
    .m_axi_bias_AWADDR(m_axi_bias_AWADDR),
    .m_axi_bias_AWLEN(m_axi_bias_AWLEN),
    .m_axi_bias_AWSIZE(m_axi_bias_AWSIZE),
    .m_axi_bias_AWBURST(m_axi_bias_AWBURST),
    .m_axi_bias_AWLOCK(m_axi_bias_AWLOCK),
    .m_axi_bias_AWREGION(m_axi_bias_AWREGION),
    .m_axi_bias_AWCACHE(m_axi_bias_AWCACHE),
    .m_axi_bias_AWPROT(m_axi_bias_AWPROT),
    .m_axi_bias_AWQOS(m_axi_bias_AWQOS),
    .m_axi_bias_AWUSER(),
    .m_axi_bias_AWVALID(m_axi_bias_AWVALID),
    .m_axi_bias_AWREADY(m_axi_bias_AWREADY),
    .m_axi_bias_WID(),
    .m_axi_bias_WDATA(m_axi_bias_WDATA),
    .m_axi_bias_WSTRB(m_axi_bias_WSTRB),
    .m_axi_bias_WLAST(m_axi_bias_WLAST),
    .m_axi_bias_WUSER(),
    .m_axi_bias_WVALID(m_axi_bias_WVALID),
    .m_axi_bias_WREADY(m_axi_bias_WREADY),
    .m_axi_bias_BID(1'B0),
    .m_axi_bias_BRESP(m_axi_bias_BRESP),
    .m_axi_bias_BUSER(1'B0),
    .m_axi_bias_BVALID(m_axi_bias_BVALID),
    .m_axi_bias_BREADY(m_axi_bias_BREADY),
    .m_axi_bias_ARID(),
    .m_axi_bias_ARADDR(m_axi_bias_ARADDR),
    .m_axi_bias_ARLEN(m_axi_bias_ARLEN),
    .m_axi_bias_ARSIZE(m_axi_bias_ARSIZE),
    .m_axi_bias_ARBURST(m_axi_bias_ARBURST),
    .m_axi_bias_ARLOCK(m_axi_bias_ARLOCK),
    .m_axi_bias_ARREGION(m_axi_bias_ARREGION),
    .m_axi_bias_ARCACHE(m_axi_bias_ARCACHE),
    .m_axi_bias_ARPROT(m_axi_bias_ARPROT),
    .m_axi_bias_ARQOS(m_axi_bias_ARQOS),
    .m_axi_bias_ARUSER(),
    .m_axi_bias_ARVALID(m_axi_bias_ARVALID),
    .m_axi_bias_ARREADY(m_axi_bias_ARREADY),
    .m_axi_bias_RID(1'B0),
    .m_axi_bias_RDATA(m_axi_bias_RDATA),
    .m_axi_bias_RRESP(m_axi_bias_RRESP),
    .m_axi_bias_RLAST(m_axi_bias_RLAST),
    .m_axi_bias_RUSER(1'B0),
    .m_axi_bias_RVALID(m_axi_bias_RVALID),
    .m_axi_bias_RREADY(m_axi_bias_RREADY)
  );
endmodule
