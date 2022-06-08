-- ==============================================================
-- Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.2 (64-bit)
-- Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
-- ==============================================================
library ieee; 
use ieee.std_logic_1164.all; 
use ieee.std_logic_unsigned.all;

entity ec_add_pow_generic_double_s_pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_12dEe is 
    generic(
             DataWidth     : integer := 105; 
             AddressWidth     : integer := 4; 
             AddressRange    : integer := 16
    ); 
    port (
          address0      : in std_logic_vector(AddressWidth-1 downto 0); 
          ce0       : in std_logic; 
          q0         : out std_logic_vector(DataWidth-1 downto 0);
          reset     : in std_logic;
          clk       : in std_logic
    ); 
end entity; 


architecture rtl of ec_add_pow_generic_double_s_pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_12dEe is 

signal address0_tmp : std_logic_vector(AddressWidth-1 downto 0); 
type mem_array is array (0 to AddressRange-1) of std_logic_vector (DataWidth-1 downto 0); 
signal mem : mem_array := (
    0 => "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", 
    1 => "000100000000000000000001010101010101010110001000100010001001000110101101000111001001100011001001111010011", 
    2 => "001000000001000000010010101111101100001100101111100011011010110000110100010000001001110111101111101000001", 
    3 => "001100000011000001010100100111010011101100101010000110001011101110000001001000111110111011110101110100101", 
    4 => "010000000110000011100111101100111111100110000010010001100101111001011010111010000000000101111001111101001", 
    5 => "010100001010000111101101001010100001001101111100110110001011011101101100001100000011000101000101110100000", 
    6 => "011000001111001110000110100011000000111011110011100100011000010100111100100101100110101111010111010001110", 
    7 => "011100010101010111010101110011011000000111010101001101100001100100110000011110111000001100001000111010111", 
    8 => "011110011000110101001100010110101011110101101111111111111101000000100110110110010011100011101000000010110", 
    9 => "100010100000100011101100111110011010010011100110010111010001111011100011110001110100111111111010101001111", 
    10 => "100110101001010110011010001001101101001110000110001011100111010100101010111100010101010100101000110000001", 
    11 => "101010110011001101110111010010111101100111100011100001100000001001111011111100111011100000010001011100111", 
    12 => "101110111110001010101000010000010001000010011110111110111010011001010001101100000100001000010000101001000", 
    13 => "110011001010001101010001010011110110100001011110010100110100011011101000011110110000011101011110000001110", 
    14 => "110111010111010110010111001100100100001101001100000110100110111111010011110000010100001011000100001110101", 
    15 => "111011100101100110011111000110010101100001011010100101011101010100001010100000110000000100110101111010010" );


begin 


memory_access_guard_0: process (address0) 
begin
      address0_tmp <= address0;
--synthesis translate_off
      if (CONV_INTEGER(address0) > AddressRange-1) then
           address0_tmp <= (others => '0');
      else 
           address0_tmp <= address0;
      end if;
--synthesis translate_on
end process;

p_rom_access: process (clk)  
begin 
    if (clk'event and clk = '1') then
        if (ce0 = '1') then 
            q0 <= mem(CONV_INTEGER(address0_tmp)); 
        end if;
    end if;
end process;

end rtl;

