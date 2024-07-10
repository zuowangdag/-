-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.2 (lin64) Build 3064766 Wed Nov 18 09:12:47 MST 2020
-- Date        : Mon Mar  6 16:48:46 2023
-- Host        : y running 64-bit Ubuntu 18.04.6 LTS
-- Command     : write_vhdl -force -mode synth_stub -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
--               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ top_top_0_0_stub.vhdl
-- Design      : top_top_0_0
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xc7z020clg484-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix is
  Port ( 
    s_axi_ctrl_AWADDR : in STD_LOGIC_VECTOR ( 7 downto 0 );
    s_axi_ctrl_AWVALID : in STD_LOGIC;
    s_axi_ctrl_AWREADY : out STD_LOGIC;
    s_axi_ctrl_WDATA : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_ctrl_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_ctrl_WVALID : in STD_LOGIC;
    s_axi_ctrl_WREADY : out STD_LOGIC;
    s_axi_ctrl_BRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_ctrl_BVALID : out STD_LOGIC;
    s_axi_ctrl_BREADY : in STD_LOGIC;
    s_axi_ctrl_ARADDR : in STD_LOGIC_VECTOR ( 7 downto 0 );
    s_axi_ctrl_ARVALID : in STD_LOGIC;
    s_axi_ctrl_ARREADY : out STD_LOGIC;
    s_axi_ctrl_RDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_ctrl_RRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_ctrl_RVALID : out STD_LOGIC;
    s_axi_ctrl_RREADY : in STD_LOGIC;
    ap_clk : in STD_LOGIC;
    ap_rst_n : in STD_LOGIC;
    interrupt : out STD_LOGIC;
    m_axi_ifm_AWADDR : out STD_LOGIC_VECTOR ( 31 downto 0 );
    m_axi_ifm_AWLEN : out STD_LOGIC_VECTOR ( 7 downto 0 );
    m_axi_ifm_AWSIZE : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_ifm_AWBURST : out STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_ifm_AWLOCK : out STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_ifm_AWREGION : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_ifm_AWCACHE : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_ifm_AWPROT : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_ifm_AWQOS : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_ifm_AWVALID : out STD_LOGIC;
    m_axi_ifm_AWREADY : in STD_LOGIC;
    m_axi_ifm_WDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    m_axi_ifm_WSTRB : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_ifm_WLAST : out STD_LOGIC;
    m_axi_ifm_WVALID : out STD_LOGIC;
    m_axi_ifm_WREADY : in STD_LOGIC;
    m_axi_ifm_BRESP : in STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_ifm_BVALID : in STD_LOGIC;
    m_axi_ifm_BREADY : out STD_LOGIC;
    m_axi_ifm_ARADDR : out STD_LOGIC_VECTOR ( 31 downto 0 );
    m_axi_ifm_ARLEN : out STD_LOGIC_VECTOR ( 7 downto 0 );
    m_axi_ifm_ARSIZE : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_ifm_ARBURST : out STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_ifm_ARLOCK : out STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_ifm_ARREGION : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_ifm_ARCACHE : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_ifm_ARPROT : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_ifm_ARQOS : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_ifm_ARVALID : out STD_LOGIC;
    m_axi_ifm_ARREADY : in STD_LOGIC;
    m_axi_ifm_RDATA : in STD_LOGIC_VECTOR ( 31 downto 0 );
    m_axi_ifm_RRESP : in STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_ifm_RLAST : in STD_LOGIC;
    m_axi_ifm_RVALID : in STD_LOGIC;
    m_axi_ifm_RREADY : out STD_LOGIC;
    m_axi_ofm_AWADDR : out STD_LOGIC_VECTOR ( 31 downto 0 );
    m_axi_ofm_AWLEN : out STD_LOGIC_VECTOR ( 7 downto 0 );
    m_axi_ofm_AWSIZE : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_ofm_AWBURST : out STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_ofm_AWLOCK : out STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_ofm_AWREGION : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_ofm_AWCACHE : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_ofm_AWPROT : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_ofm_AWQOS : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_ofm_AWVALID : out STD_LOGIC;
    m_axi_ofm_AWREADY : in STD_LOGIC;
    m_axi_ofm_WDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    m_axi_ofm_WSTRB : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_ofm_WLAST : out STD_LOGIC;
    m_axi_ofm_WVALID : out STD_LOGIC;
    m_axi_ofm_WREADY : in STD_LOGIC;
    m_axi_ofm_BRESP : in STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_ofm_BVALID : in STD_LOGIC;
    m_axi_ofm_BREADY : out STD_LOGIC;
    m_axi_ofm_ARADDR : out STD_LOGIC_VECTOR ( 31 downto 0 );
    m_axi_ofm_ARLEN : out STD_LOGIC_VECTOR ( 7 downto 0 );
    m_axi_ofm_ARSIZE : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_ofm_ARBURST : out STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_ofm_ARLOCK : out STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_ofm_ARREGION : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_ofm_ARCACHE : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_ofm_ARPROT : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_ofm_ARQOS : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_ofm_ARVALID : out STD_LOGIC;
    m_axi_ofm_ARREADY : in STD_LOGIC;
    m_axi_ofm_RDATA : in STD_LOGIC_VECTOR ( 31 downto 0 );
    m_axi_ofm_RRESP : in STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_ofm_RLAST : in STD_LOGIC;
    m_axi_ofm_RVALID : in STD_LOGIC;
    m_axi_ofm_RREADY : out STD_LOGIC;
    m_axi_weights_AWADDR : out STD_LOGIC_VECTOR ( 31 downto 0 );
    m_axi_weights_AWLEN : out STD_LOGIC_VECTOR ( 7 downto 0 );
    m_axi_weights_AWSIZE : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_weights_AWBURST : out STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_weights_AWLOCK : out STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_weights_AWREGION : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_weights_AWCACHE : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_weights_AWPROT : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_weights_AWQOS : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_weights_AWVALID : out STD_LOGIC;
    m_axi_weights_AWREADY : in STD_LOGIC;
    m_axi_weights_WDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    m_axi_weights_WSTRB : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_weights_WLAST : out STD_LOGIC;
    m_axi_weights_WVALID : out STD_LOGIC;
    m_axi_weights_WREADY : in STD_LOGIC;
    m_axi_weights_BRESP : in STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_weights_BVALID : in STD_LOGIC;
    m_axi_weights_BREADY : out STD_LOGIC;
    m_axi_weights_ARADDR : out STD_LOGIC_VECTOR ( 31 downto 0 );
    m_axi_weights_ARLEN : out STD_LOGIC_VECTOR ( 7 downto 0 );
    m_axi_weights_ARSIZE : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_weights_ARBURST : out STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_weights_ARLOCK : out STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_weights_ARREGION : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_weights_ARCACHE : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_weights_ARPROT : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_weights_ARQOS : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_weights_ARVALID : out STD_LOGIC;
    m_axi_weights_ARREADY : in STD_LOGIC;
    m_axi_weights_RDATA : in STD_LOGIC_VECTOR ( 31 downto 0 );
    m_axi_weights_RRESP : in STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_weights_RLAST : in STD_LOGIC;
    m_axi_weights_RVALID : in STD_LOGIC;
    m_axi_weights_RREADY : out STD_LOGIC;
    m_axi_bias_AWADDR : out STD_LOGIC_VECTOR ( 31 downto 0 );
    m_axi_bias_AWLEN : out STD_LOGIC_VECTOR ( 7 downto 0 );
    m_axi_bias_AWSIZE : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_bias_AWBURST : out STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_bias_AWLOCK : out STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_bias_AWREGION : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_bias_AWCACHE : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_bias_AWPROT : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_bias_AWQOS : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_bias_AWVALID : out STD_LOGIC;
    m_axi_bias_AWREADY : in STD_LOGIC;
    m_axi_bias_WDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    m_axi_bias_WSTRB : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_bias_WLAST : out STD_LOGIC;
    m_axi_bias_WVALID : out STD_LOGIC;
    m_axi_bias_WREADY : in STD_LOGIC;
    m_axi_bias_BRESP : in STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_bias_BVALID : in STD_LOGIC;
    m_axi_bias_BREADY : out STD_LOGIC;
    m_axi_bias_ARADDR : out STD_LOGIC_VECTOR ( 31 downto 0 );
    m_axi_bias_ARLEN : out STD_LOGIC_VECTOR ( 7 downto 0 );
    m_axi_bias_ARSIZE : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_bias_ARBURST : out STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_bias_ARLOCK : out STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_bias_ARREGION : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_bias_ARCACHE : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_bias_ARPROT : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_bias_ARQOS : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_bias_ARVALID : out STD_LOGIC;
    m_axi_bias_ARREADY : in STD_LOGIC;
    m_axi_bias_RDATA : in STD_LOGIC_VECTOR ( 31 downto 0 );
    m_axi_bias_RRESP : in STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_bias_RLAST : in STD_LOGIC;
    m_axi_bias_RVALID : in STD_LOGIC;
    m_axi_bias_RREADY : out STD_LOGIC
  );

end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix;

architecture stub of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "s_axi_ctrl_AWADDR[7:0],s_axi_ctrl_AWVALID,s_axi_ctrl_AWREADY,s_axi_ctrl_WDATA[31:0],s_axi_ctrl_WSTRB[3:0],s_axi_ctrl_WVALID,s_axi_ctrl_WREADY,s_axi_ctrl_BRESP[1:0],s_axi_ctrl_BVALID,s_axi_ctrl_BREADY,s_axi_ctrl_ARADDR[7:0],s_axi_ctrl_ARVALID,s_axi_ctrl_ARREADY,s_axi_ctrl_RDATA[31:0],s_axi_ctrl_RRESP[1:0],s_axi_ctrl_RVALID,s_axi_ctrl_RREADY,ap_clk,ap_rst_n,interrupt,m_axi_ifm_AWADDR[31:0],m_axi_ifm_AWLEN[7:0],m_axi_ifm_AWSIZE[2:0],m_axi_ifm_AWBURST[1:0],m_axi_ifm_AWLOCK[1:0],m_axi_ifm_AWREGION[3:0],m_axi_ifm_AWCACHE[3:0],m_axi_ifm_AWPROT[2:0],m_axi_ifm_AWQOS[3:0],m_axi_ifm_AWVALID,m_axi_ifm_AWREADY,m_axi_ifm_WDATA[31:0],m_axi_ifm_WSTRB[3:0],m_axi_ifm_WLAST,m_axi_ifm_WVALID,m_axi_ifm_WREADY,m_axi_ifm_BRESP[1:0],m_axi_ifm_BVALID,m_axi_ifm_BREADY,m_axi_ifm_ARADDR[31:0],m_axi_ifm_ARLEN[7:0],m_axi_ifm_ARSIZE[2:0],m_axi_ifm_ARBURST[1:0],m_axi_ifm_ARLOCK[1:0],m_axi_ifm_ARREGION[3:0],m_axi_ifm_ARCACHE[3:0],m_axi_ifm_ARPROT[2:0],m_axi_ifm_ARQOS[3:0],m_axi_ifm_ARVALID,m_axi_ifm_ARREADY,m_axi_ifm_RDATA[31:0],m_axi_ifm_RRESP[1:0],m_axi_ifm_RLAST,m_axi_ifm_RVALID,m_axi_ifm_RREADY,m_axi_ofm_AWADDR[31:0],m_axi_ofm_AWLEN[7:0],m_axi_ofm_AWSIZE[2:0],m_axi_ofm_AWBURST[1:0],m_axi_ofm_AWLOCK[1:0],m_axi_ofm_AWREGION[3:0],m_axi_ofm_AWCACHE[3:0],m_axi_ofm_AWPROT[2:0],m_axi_ofm_AWQOS[3:0],m_axi_ofm_AWVALID,m_axi_ofm_AWREADY,m_axi_ofm_WDATA[31:0],m_axi_ofm_WSTRB[3:0],m_axi_ofm_WLAST,m_axi_ofm_WVALID,m_axi_ofm_WREADY,m_axi_ofm_BRESP[1:0],m_axi_ofm_BVALID,m_axi_ofm_BREADY,m_axi_ofm_ARADDR[31:0],m_axi_ofm_ARLEN[7:0],m_axi_ofm_ARSIZE[2:0],m_axi_ofm_ARBURST[1:0],m_axi_ofm_ARLOCK[1:0],m_axi_ofm_ARREGION[3:0],m_axi_ofm_ARCACHE[3:0],m_axi_ofm_ARPROT[2:0],m_axi_ofm_ARQOS[3:0],m_axi_ofm_ARVALID,m_axi_ofm_ARREADY,m_axi_ofm_RDATA[31:0],m_axi_ofm_RRESP[1:0],m_axi_ofm_RLAST,m_axi_ofm_RVALID,m_axi_ofm_RREADY,m_axi_weights_AWADDR[31:0],m_axi_weights_AWLEN[7:0],m_axi_weights_AWSIZE[2:0],m_axi_weights_AWBURST[1:0],m_axi_weights_AWLOCK[1:0],m_axi_weights_AWREGION[3:0],m_axi_weights_AWCACHE[3:0],m_axi_weights_AWPROT[2:0],m_axi_weights_AWQOS[3:0],m_axi_weights_AWVALID,m_axi_weights_AWREADY,m_axi_weights_WDATA[31:0],m_axi_weights_WSTRB[3:0],m_axi_weights_WLAST,m_axi_weights_WVALID,m_axi_weights_WREADY,m_axi_weights_BRESP[1:0],m_axi_weights_BVALID,m_axi_weights_BREADY,m_axi_weights_ARADDR[31:0],m_axi_weights_ARLEN[7:0],m_axi_weights_ARSIZE[2:0],m_axi_weights_ARBURST[1:0],m_axi_weights_ARLOCK[1:0],m_axi_weights_ARREGION[3:0],m_axi_weights_ARCACHE[3:0],m_axi_weights_ARPROT[2:0],m_axi_weights_ARQOS[3:0],m_axi_weights_ARVALID,m_axi_weights_ARREADY,m_axi_weights_RDATA[31:0],m_axi_weights_RRESP[1:0],m_axi_weights_RLAST,m_axi_weights_RVALID,m_axi_weights_RREADY,m_axi_bias_AWADDR[31:0],m_axi_bias_AWLEN[7:0],m_axi_bias_AWSIZE[2:0],m_axi_bias_AWBURST[1:0],m_axi_bias_AWLOCK[1:0],m_axi_bias_AWREGION[3:0],m_axi_bias_AWCACHE[3:0],m_axi_bias_AWPROT[2:0],m_axi_bias_AWQOS[3:0],m_axi_bias_AWVALID,m_axi_bias_AWREADY,m_axi_bias_WDATA[31:0],m_axi_bias_WSTRB[3:0],m_axi_bias_WLAST,m_axi_bias_WVALID,m_axi_bias_WREADY,m_axi_bias_BRESP[1:0],m_axi_bias_BVALID,m_axi_bias_BREADY,m_axi_bias_ARADDR[31:0],m_axi_bias_ARLEN[7:0],m_axi_bias_ARSIZE[2:0],m_axi_bias_ARBURST[1:0],m_axi_bias_ARLOCK[1:0],m_axi_bias_ARREGION[3:0],m_axi_bias_ARCACHE[3:0],m_axi_bias_ARPROT[2:0],m_axi_bias_ARQOS[3:0],m_axi_bias_ARVALID,m_axi_bias_ARREADY,m_axi_bias_RDATA[31:0],m_axi_bias_RRESP[1:0],m_axi_bias_RLAST,m_axi_bias_RVALID,m_axi_bias_RREADY";
attribute X_CORE_INFO : string;
attribute X_CORE_INFO of stub : architecture is "top,Vivado 2020.2";
begin
end;
