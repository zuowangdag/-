// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.2 (lin64) Build 3064766 Wed Nov 18 09:12:47 MST 2020
// Date        : Mon Mar  6 16:48:46 2023
// Host        : y running 64-bit Ubuntu 18.04.6 LTS
// Command     : write_verilog -force -mode synth_stub -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
//               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ top_top_0_0_stub.v
// Design      : top_top_0_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7z020clg484-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "top,Vivado 2020.2" *)
module decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix(s_axi_ctrl_AWADDR, s_axi_ctrl_AWVALID, 
  s_axi_ctrl_AWREADY, s_axi_ctrl_WDATA, s_axi_ctrl_WSTRB, s_axi_ctrl_WVALID, 
  s_axi_ctrl_WREADY, s_axi_ctrl_BRESP, s_axi_ctrl_BVALID, s_axi_ctrl_BREADY, 
  s_axi_ctrl_ARADDR, s_axi_ctrl_ARVALID, s_axi_ctrl_ARREADY, s_axi_ctrl_RDATA, 
  s_axi_ctrl_RRESP, s_axi_ctrl_RVALID, s_axi_ctrl_RREADY, ap_clk, ap_rst_n, interrupt, 
  m_axi_ifm_AWADDR, m_axi_ifm_AWLEN, m_axi_ifm_AWSIZE, m_axi_ifm_AWBURST, m_axi_ifm_AWLOCK, 
  m_axi_ifm_AWREGION, m_axi_ifm_AWCACHE, m_axi_ifm_AWPROT, m_axi_ifm_AWQOS, 
  m_axi_ifm_AWVALID, m_axi_ifm_AWREADY, m_axi_ifm_WDATA, m_axi_ifm_WSTRB, m_axi_ifm_WLAST, 
  m_axi_ifm_WVALID, m_axi_ifm_WREADY, m_axi_ifm_BRESP, m_axi_ifm_BVALID, m_axi_ifm_BREADY, 
  m_axi_ifm_ARADDR, m_axi_ifm_ARLEN, m_axi_ifm_ARSIZE, m_axi_ifm_ARBURST, m_axi_ifm_ARLOCK, 
  m_axi_ifm_ARREGION, m_axi_ifm_ARCACHE, m_axi_ifm_ARPROT, m_axi_ifm_ARQOS, 
  m_axi_ifm_ARVALID, m_axi_ifm_ARREADY, m_axi_ifm_RDATA, m_axi_ifm_RRESP, m_axi_ifm_RLAST, 
  m_axi_ifm_RVALID, m_axi_ifm_RREADY, m_axi_ofm_AWADDR, m_axi_ofm_AWLEN, m_axi_ofm_AWSIZE, 
  m_axi_ofm_AWBURST, m_axi_ofm_AWLOCK, m_axi_ofm_AWREGION, m_axi_ofm_AWCACHE, 
  m_axi_ofm_AWPROT, m_axi_ofm_AWQOS, m_axi_ofm_AWVALID, m_axi_ofm_AWREADY, m_axi_ofm_WDATA, 
  m_axi_ofm_WSTRB, m_axi_ofm_WLAST, m_axi_ofm_WVALID, m_axi_ofm_WREADY, m_axi_ofm_BRESP, 
  m_axi_ofm_BVALID, m_axi_ofm_BREADY, m_axi_ofm_ARADDR, m_axi_ofm_ARLEN, m_axi_ofm_ARSIZE, 
  m_axi_ofm_ARBURST, m_axi_ofm_ARLOCK, m_axi_ofm_ARREGION, m_axi_ofm_ARCACHE, 
  m_axi_ofm_ARPROT, m_axi_ofm_ARQOS, m_axi_ofm_ARVALID, m_axi_ofm_ARREADY, m_axi_ofm_RDATA, 
  m_axi_ofm_RRESP, m_axi_ofm_RLAST, m_axi_ofm_RVALID, m_axi_ofm_RREADY, 
  m_axi_weights_AWADDR, m_axi_weights_AWLEN, m_axi_weights_AWSIZE, m_axi_weights_AWBURST, 
  m_axi_weights_AWLOCK, m_axi_weights_AWREGION, m_axi_weights_AWCACHE, 
  m_axi_weights_AWPROT, m_axi_weights_AWQOS, m_axi_weights_AWVALID, 
  m_axi_weights_AWREADY, m_axi_weights_WDATA, m_axi_weights_WSTRB, m_axi_weights_WLAST, 
  m_axi_weights_WVALID, m_axi_weights_WREADY, m_axi_weights_BRESP, m_axi_weights_BVALID, 
  m_axi_weights_BREADY, m_axi_weights_ARADDR, m_axi_weights_ARLEN, m_axi_weights_ARSIZE, 
  m_axi_weights_ARBURST, m_axi_weights_ARLOCK, m_axi_weights_ARREGION, 
  m_axi_weights_ARCACHE, m_axi_weights_ARPROT, m_axi_weights_ARQOS, 
  m_axi_weights_ARVALID, m_axi_weights_ARREADY, m_axi_weights_RDATA, m_axi_weights_RRESP, 
  m_axi_weights_RLAST, m_axi_weights_RVALID, m_axi_weights_RREADY, m_axi_bias_AWADDR, 
  m_axi_bias_AWLEN, m_axi_bias_AWSIZE, m_axi_bias_AWBURST, m_axi_bias_AWLOCK, 
  m_axi_bias_AWREGION, m_axi_bias_AWCACHE, m_axi_bias_AWPROT, m_axi_bias_AWQOS, 
  m_axi_bias_AWVALID, m_axi_bias_AWREADY, m_axi_bias_WDATA, m_axi_bias_WSTRB, 
  m_axi_bias_WLAST, m_axi_bias_WVALID, m_axi_bias_WREADY, m_axi_bias_BRESP, 
  m_axi_bias_BVALID, m_axi_bias_BREADY, m_axi_bias_ARADDR, m_axi_bias_ARLEN, 
  m_axi_bias_ARSIZE, m_axi_bias_ARBURST, m_axi_bias_ARLOCK, m_axi_bias_ARREGION, 
  m_axi_bias_ARCACHE, m_axi_bias_ARPROT, m_axi_bias_ARQOS, m_axi_bias_ARVALID, 
  m_axi_bias_ARREADY, m_axi_bias_RDATA, m_axi_bias_RRESP, m_axi_bias_RLAST, 
  m_axi_bias_RVALID, m_axi_bias_RREADY)
/* synthesis syn_black_box black_box_pad_pin="s_axi_ctrl_AWADDR[7:0],s_axi_ctrl_AWVALID,s_axi_ctrl_AWREADY,s_axi_ctrl_WDATA[31:0],s_axi_ctrl_WSTRB[3:0],s_axi_ctrl_WVALID,s_axi_ctrl_WREADY,s_axi_ctrl_BRESP[1:0],s_axi_ctrl_BVALID,s_axi_ctrl_BREADY,s_axi_ctrl_ARADDR[7:0],s_axi_ctrl_ARVALID,s_axi_ctrl_ARREADY,s_axi_ctrl_RDATA[31:0],s_axi_ctrl_RRESP[1:0],s_axi_ctrl_RVALID,s_axi_ctrl_RREADY,ap_clk,ap_rst_n,interrupt,m_axi_ifm_AWADDR[31:0],m_axi_ifm_AWLEN[7:0],m_axi_ifm_AWSIZE[2:0],m_axi_ifm_AWBURST[1:0],m_axi_ifm_AWLOCK[1:0],m_axi_ifm_AWREGION[3:0],m_axi_ifm_AWCACHE[3:0],m_axi_ifm_AWPROT[2:0],m_axi_ifm_AWQOS[3:0],m_axi_ifm_AWVALID,m_axi_ifm_AWREADY,m_axi_ifm_WDATA[31:0],m_axi_ifm_WSTRB[3:0],m_axi_ifm_WLAST,m_axi_ifm_WVALID,m_axi_ifm_WREADY,m_axi_ifm_BRESP[1:0],m_axi_ifm_BVALID,m_axi_ifm_BREADY,m_axi_ifm_ARADDR[31:0],m_axi_ifm_ARLEN[7:0],m_axi_ifm_ARSIZE[2:0],m_axi_ifm_ARBURST[1:0],m_axi_ifm_ARLOCK[1:0],m_axi_ifm_ARREGION[3:0],m_axi_ifm_ARCACHE[3:0],m_axi_ifm_ARPROT[2:0],m_axi_ifm_ARQOS[3:0],m_axi_ifm_ARVALID,m_axi_ifm_ARREADY,m_axi_ifm_RDATA[31:0],m_axi_ifm_RRESP[1:0],m_axi_ifm_RLAST,m_axi_ifm_RVALID,m_axi_ifm_RREADY,m_axi_ofm_AWADDR[31:0],m_axi_ofm_AWLEN[7:0],m_axi_ofm_AWSIZE[2:0],m_axi_ofm_AWBURST[1:0],m_axi_ofm_AWLOCK[1:0],m_axi_ofm_AWREGION[3:0],m_axi_ofm_AWCACHE[3:0],m_axi_ofm_AWPROT[2:0],m_axi_ofm_AWQOS[3:0],m_axi_ofm_AWVALID,m_axi_ofm_AWREADY,m_axi_ofm_WDATA[31:0],m_axi_ofm_WSTRB[3:0],m_axi_ofm_WLAST,m_axi_ofm_WVALID,m_axi_ofm_WREADY,m_axi_ofm_BRESP[1:0],m_axi_ofm_BVALID,m_axi_ofm_BREADY,m_axi_ofm_ARADDR[31:0],m_axi_ofm_ARLEN[7:0],m_axi_ofm_ARSIZE[2:0],m_axi_ofm_ARBURST[1:0],m_axi_ofm_ARLOCK[1:0],m_axi_ofm_ARREGION[3:0],m_axi_ofm_ARCACHE[3:0],m_axi_ofm_ARPROT[2:0],m_axi_ofm_ARQOS[3:0],m_axi_ofm_ARVALID,m_axi_ofm_ARREADY,m_axi_ofm_RDATA[31:0],m_axi_ofm_RRESP[1:0],m_axi_ofm_RLAST,m_axi_ofm_RVALID,m_axi_ofm_RREADY,m_axi_weights_AWADDR[31:0],m_axi_weights_AWLEN[7:0],m_axi_weights_AWSIZE[2:0],m_axi_weights_AWBURST[1:0],m_axi_weights_AWLOCK[1:0],m_axi_weights_AWREGION[3:0],m_axi_weights_AWCACHE[3:0],m_axi_weights_AWPROT[2:0],m_axi_weights_AWQOS[3:0],m_axi_weights_AWVALID,m_axi_weights_AWREADY,m_axi_weights_WDATA[31:0],m_axi_weights_WSTRB[3:0],m_axi_weights_WLAST,m_axi_weights_WVALID,m_axi_weights_WREADY,m_axi_weights_BRESP[1:0],m_axi_weights_BVALID,m_axi_weights_BREADY,m_axi_weights_ARADDR[31:0],m_axi_weights_ARLEN[7:0],m_axi_weights_ARSIZE[2:0],m_axi_weights_ARBURST[1:0],m_axi_weights_ARLOCK[1:0],m_axi_weights_ARREGION[3:0],m_axi_weights_ARCACHE[3:0],m_axi_weights_ARPROT[2:0],m_axi_weights_ARQOS[3:0],m_axi_weights_ARVALID,m_axi_weights_ARREADY,m_axi_weights_RDATA[31:0],m_axi_weights_RRESP[1:0],m_axi_weights_RLAST,m_axi_weights_RVALID,m_axi_weights_RREADY,m_axi_bias_AWADDR[31:0],m_axi_bias_AWLEN[7:0],m_axi_bias_AWSIZE[2:0],m_axi_bias_AWBURST[1:0],m_axi_bias_AWLOCK[1:0],m_axi_bias_AWREGION[3:0],m_axi_bias_AWCACHE[3:0],m_axi_bias_AWPROT[2:0],m_axi_bias_AWQOS[3:0],m_axi_bias_AWVALID,m_axi_bias_AWREADY,m_axi_bias_WDATA[31:0],m_axi_bias_WSTRB[3:0],m_axi_bias_WLAST,m_axi_bias_WVALID,m_axi_bias_WREADY,m_axi_bias_BRESP[1:0],m_axi_bias_BVALID,m_axi_bias_BREADY,m_axi_bias_ARADDR[31:0],m_axi_bias_ARLEN[7:0],m_axi_bias_ARSIZE[2:0],m_axi_bias_ARBURST[1:0],m_axi_bias_ARLOCK[1:0],m_axi_bias_ARREGION[3:0],m_axi_bias_ARCACHE[3:0],m_axi_bias_ARPROT[2:0],m_axi_bias_ARQOS[3:0],m_axi_bias_ARVALID,m_axi_bias_ARREADY,m_axi_bias_RDATA[31:0],m_axi_bias_RRESP[1:0],m_axi_bias_RLAST,m_axi_bias_RVALID,m_axi_bias_RREADY" */;
  input [7:0]s_axi_ctrl_AWADDR;
  input s_axi_ctrl_AWVALID;
  output s_axi_ctrl_AWREADY;
  input [31:0]s_axi_ctrl_WDATA;
  input [3:0]s_axi_ctrl_WSTRB;
  input s_axi_ctrl_WVALID;
  output s_axi_ctrl_WREADY;
  output [1:0]s_axi_ctrl_BRESP;
  output s_axi_ctrl_BVALID;
  input s_axi_ctrl_BREADY;
  input [7:0]s_axi_ctrl_ARADDR;
  input s_axi_ctrl_ARVALID;
  output s_axi_ctrl_ARREADY;
  output [31:0]s_axi_ctrl_RDATA;
  output [1:0]s_axi_ctrl_RRESP;
  output s_axi_ctrl_RVALID;
  input s_axi_ctrl_RREADY;
  input ap_clk;
  input ap_rst_n;
  output interrupt;
  output [31:0]m_axi_ifm_AWADDR;
  output [7:0]m_axi_ifm_AWLEN;
  output [2:0]m_axi_ifm_AWSIZE;
  output [1:0]m_axi_ifm_AWBURST;
  output [1:0]m_axi_ifm_AWLOCK;
  output [3:0]m_axi_ifm_AWREGION;
  output [3:0]m_axi_ifm_AWCACHE;
  output [2:0]m_axi_ifm_AWPROT;
  output [3:0]m_axi_ifm_AWQOS;
  output m_axi_ifm_AWVALID;
  input m_axi_ifm_AWREADY;
  output [31:0]m_axi_ifm_WDATA;
  output [3:0]m_axi_ifm_WSTRB;
  output m_axi_ifm_WLAST;
  output m_axi_ifm_WVALID;
  input m_axi_ifm_WREADY;
  input [1:0]m_axi_ifm_BRESP;
  input m_axi_ifm_BVALID;
  output m_axi_ifm_BREADY;
  output [31:0]m_axi_ifm_ARADDR;
  output [7:0]m_axi_ifm_ARLEN;
  output [2:0]m_axi_ifm_ARSIZE;
  output [1:0]m_axi_ifm_ARBURST;
  output [1:0]m_axi_ifm_ARLOCK;
  output [3:0]m_axi_ifm_ARREGION;
  output [3:0]m_axi_ifm_ARCACHE;
  output [2:0]m_axi_ifm_ARPROT;
  output [3:0]m_axi_ifm_ARQOS;
  output m_axi_ifm_ARVALID;
  input m_axi_ifm_ARREADY;
  input [31:0]m_axi_ifm_RDATA;
  input [1:0]m_axi_ifm_RRESP;
  input m_axi_ifm_RLAST;
  input m_axi_ifm_RVALID;
  output m_axi_ifm_RREADY;
  output [31:0]m_axi_ofm_AWADDR;
  output [7:0]m_axi_ofm_AWLEN;
  output [2:0]m_axi_ofm_AWSIZE;
  output [1:0]m_axi_ofm_AWBURST;
  output [1:0]m_axi_ofm_AWLOCK;
  output [3:0]m_axi_ofm_AWREGION;
  output [3:0]m_axi_ofm_AWCACHE;
  output [2:0]m_axi_ofm_AWPROT;
  output [3:0]m_axi_ofm_AWQOS;
  output m_axi_ofm_AWVALID;
  input m_axi_ofm_AWREADY;
  output [31:0]m_axi_ofm_WDATA;
  output [3:0]m_axi_ofm_WSTRB;
  output m_axi_ofm_WLAST;
  output m_axi_ofm_WVALID;
  input m_axi_ofm_WREADY;
  input [1:0]m_axi_ofm_BRESP;
  input m_axi_ofm_BVALID;
  output m_axi_ofm_BREADY;
  output [31:0]m_axi_ofm_ARADDR;
  output [7:0]m_axi_ofm_ARLEN;
  output [2:0]m_axi_ofm_ARSIZE;
  output [1:0]m_axi_ofm_ARBURST;
  output [1:0]m_axi_ofm_ARLOCK;
  output [3:0]m_axi_ofm_ARREGION;
  output [3:0]m_axi_ofm_ARCACHE;
  output [2:0]m_axi_ofm_ARPROT;
  output [3:0]m_axi_ofm_ARQOS;
  output m_axi_ofm_ARVALID;
  input m_axi_ofm_ARREADY;
  input [31:0]m_axi_ofm_RDATA;
  input [1:0]m_axi_ofm_RRESP;
  input m_axi_ofm_RLAST;
  input m_axi_ofm_RVALID;
  output m_axi_ofm_RREADY;
  output [31:0]m_axi_weights_AWADDR;
  output [7:0]m_axi_weights_AWLEN;
  output [2:0]m_axi_weights_AWSIZE;
  output [1:0]m_axi_weights_AWBURST;
  output [1:0]m_axi_weights_AWLOCK;
  output [3:0]m_axi_weights_AWREGION;
  output [3:0]m_axi_weights_AWCACHE;
  output [2:0]m_axi_weights_AWPROT;
  output [3:0]m_axi_weights_AWQOS;
  output m_axi_weights_AWVALID;
  input m_axi_weights_AWREADY;
  output [31:0]m_axi_weights_WDATA;
  output [3:0]m_axi_weights_WSTRB;
  output m_axi_weights_WLAST;
  output m_axi_weights_WVALID;
  input m_axi_weights_WREADY;
  input [1:0]m_axi_weights_BRESP;
  input m_axi_weights_BVALID;
  output m_axi_weights_BREADY;
  output [31:0]m_axi_weights_ARADDR;
  output [7:0]m_axi_weights_ARLEN;
  output [2:0]m_axi_weights_ARSIZE;
  output [1:0]m_axi_weights_ARBURST;
  output [1:0]m_axi_weights_ARLOCK;
  output [3:0]m_axi_weights_ARREGION;
  output [3:0]m_axi_weights_ARCACHE;
  output [2:0]m_axi_weights_ARPROT;
  output [3:0]m_axi_weights_ARQOS;
  output m_axi_weights_ARVALID;
  input m_axi_weights_ARREADY;
  input [31:0]m_axi_weights_RDATA;
  input [1:0]m_axi_weights_RRESP;
  input m_axi_weights_RLAST;
  input m_axi_weights_RVALID;
  output m_axi_weights_RREADY;
  output [31:0]m_axi_bias_AWADDR;
  output [7:0]m_axi_bias_AWLEN;
  output [2:0]m_axi_bias_AWSIZE;
  output [1:0]m_axi_bias_AWBURST;
  output [1:0]m_axi_bias_AWLOCK;
  output [3:0]m_axi_bias_AWREGION;
  output [3:0]m_axi_bias_AWCACHE;
  output [2:0]m_axi_bias_AWPROT;
  output [3:0]m_axi_bias_AWQOS;
  output m_axi_bias_AWVALID;
  input m_axi_bias_AWREADY;
  output [31:0]m_axi_bias_WDATA;
  output [3:0]m_axi_bias_WSTRB;
  output m_axi_bias_WLAST;
  output m_axi_bias_WVALID;
  input m_axi_bias_WREADY;
  input [1:0]m_axi_bias_BRESP;
  input m_axi_bias_BVALID;
  output m_axi_bias_BREADY;
  output [31:0]m_axi_bias_ARADDR;
  output [7:0]m_axi_bias_ARLEN;
  output [2:0]m_axi_bias_ARSIZE;
  output [1:0]m_axi_bias_ARBURST;
  output [1:0]m_axi_bias_ARLOCK;
  output [3:0]m_axi_bias_ARREGION;
  output [3:0]m_axi_bias_ARCACHE;
  output [2:0]m_axi_bias_ARPROT;
  output [3:0]m_axi_bias_ARQOS;
  output m_axi_bias_ARVALID;
  input m_axi_bias_ARREADY;
  input [31:0]m_axi_bias_RDATA;
  input [1:0]m_axi_bias_RRESP;
  input m_axi_bias_RLAST;
  input m_axi_bias_RVALID;
  output m_axi_bias_RREADY;
endmodule
