-- ==============================================================
-- Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.2 (64-bit)
-- Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
-- ==============================================================
library ieee; 
use ieee.std_logic_1164.all; 
use ieee.std_logic_unsigned.all;

entity ec_add_pow_generic_double_s_pow_reduce_anonymous_namespace_table_f_Z3_ap_ufixed_59_0lbW is 
    generic(
             DataWidth     : integer := 26; 
             AddressWidth     : integer := 8; 
             AddressRange    : integer := 256
    ); 
    port (
          address0      : in std_logic_vector(AddressWidth-1 downto 0); 
          ce0       : in std_logic; 
          q0         : out std_logic_vector(DataWidth-1 downto 0);
          address1      : in std_logic_vector(AddressWidth-1 downto 0); 
          ce1       : in std_logic; 
          q1         : out std_logic_vector(DataWidth-1 downto 0);
          reset     : in std_logic;
          clk       : in std_logic
    ); 
end entity; 


architecture rtl of ec_add_pow_generic_double_s_pow_reduce_anonymous_namespace_table_f_Z3_ap_ufixed_59_0lbW is 

signal address0_tmp : std_logic_vector(AddressWidth-1 downto 0); 
signal address1_tmp : std_logic_vector(AddressWidth-1 downto 0); 
type mem_array is array (0 to AddressRange-1) of std_logic_vector (DataWidth-1 downto 0); 
signal mem : mem_array := (
    0 => "00000000000000000000000000", 1 => "00000000000000010000000000", 
    2 => "00000000000001000000000000", 3 => "00000000000010010000000000", 
    4 => "00000000000100000000000000", 5 => "00000000000110010000000000", 
    6 => "00000000001001000000000000", 7 => "00000000001100010000000000", 
    8 => "00000000010000000000000000", 9 => "00000000010100010000000000", 
    10 => "00000000011001000000000000", 11 => "00000000011110010000000000", 
    12 => "00000000100100000000000000", 13 => "00000000101010010000000000", 
    14 => "00000000110001000000000000", 15 => "00000000111000010000000000", 
    16 => "00000001000000000000000000", 17 => "00000001001000010000000000", 
    18 => "00000001010001000000000000", 19 => "00000001011010010000000000", 
    20 => "00000001100100000000000000", 21 => "00000001101110010000000000", 
    22 => "00000001111001000000000000", 23 => "00000010000100010000000000", 
    24 => "00000010010000000000000000", 25 => "00000010011100010000000000", 
    26 => "00000010101001000000000000", 27 => "00000010110110010000000000", 
    28 => "00000011000100000000000000", 29 => "00000011010010010000000000", 
    30 => "00000011100001000000000000", 31 => "00000011110000010000000000", 
    32 => "00000100000000000000000000", 33 => "00000100010000010000000000", 
    34 => "00000100100001000000000000", 35 => "00000100110010010000000000", 
    36 => "00000101000100000000000000", 37 => "00000101010110010000000001", 
    38 => "00000101101001000000000001", 39 => "00000101111100010000000001", 
    40 => "00000110010000000000000001", 41 => "00000110100100010000000001", 
    42 => "00000110111001000000000001", 43 => "00000111001110010000000001", 
    44 => "00000111100100000000000001", 45 => "00000111111010010000000001", 
    46 => "00001000010001000000000001", 47 => "00001000101000010000000010", 
    48 => "00001001000000000000000010", 49 => "00001001011000010000000010", 
    50 => "00001001110001000000000010", 51 => "00001010001010010000000010", 
    52 => "00001010100100000000000010", 53 => "00001010111110010000000011", 
    54 => "00001011011001000000000011", 55 => "00001011110100010000000011", 
    56 => "00001100010000000000000011", 57 => "00001100101100010000000011", 
    58 => "00001101001001000000000011", 59 => "00001101100110010000000100", 
    60 => "00001110000100000000000100", 61 => "00001110100010010000000100", 
    62 => "00001111000001000000000100", 63 => "00001111100000010000000101", 
    64 => "00010000000000000000000101", 65 => "00010000100000010000000101", 
    66 => "00010001000001000000000101", 67 => "00010001100010010000000110", 
    68 => "00010010000100000000000110", 69 => "00010010100110010000000110", 
    70 => "00010011001001000000000110", 71 => "00010011101100010000000111", 
    72 => "00010100010000000000000111", 73 => "00010100110100010000000111", 
    74 => "00010101011001000000001000", 75 => "00010101111110010000001000", 
    76 => "00010110100100000000001000", 77 => "00010111001010010000001001", 
    78 => "00010111110001000000001001", 79 => "00011000011000010000001010", 
    80 => "00011001000000000000001010", 81 => "00011001101000010000001010", 
    82 => "00011010010001000000001011", 83 => "00011010111010010000001011", 
    84 => "00011011100100000000001100", 85 => "00011100001110010000001100", 
    86 => "00011100111001000000001100", 87 => "00011101100100010000001101", 
    88 => "00011110010000000000001101", 89 => "00011110111100010000001110", 
    90 => "00011111101001000000001110", 91 => "00100000010110010000001111", 
    92 => "00100001000100000000001111", 93 => "00100001110010010000010000", 
    94 => "00100010100001000000010000", 95 => "00100011010000010000010001", 
    96 => "00100100000000000000010010", 97 => "00100100110000010000010010", 
    98 => "00100101100001000000010011", 99 => "00100110010010010000010011", 
    100 => "00100111000100000000010100", 101 => "00100111110110010000010100", 
    102 => "00101000101001000000010101", 103 => "00101001011100010000010110", 
    104 => "00101010010000000000010110", 105 => "00101011000100010000010111", 
    106 => "00101011111001000000011000", 107 => "00101100101110010000011000", 
    108 => "00101101100100000000011001", 109 => "00101110011010010000011010", 
    110 => "00101111010001000000011011", 111 => "00110000001000010000011011", 
    112 => "00110001000000000000011100", 113 => "00110001111000010000011101", 
    114 => "00110010110001000000011110", 115 => "00110011101010010000011110", 
    116 => "00110100100100000000011111", 117 => "00110101011110010000100000", 
    118 => "00110110011001000000100001", 119 => "00110111010100010000100010", 
    120 => "00111000010000000000100011", 121 => "00111001001100010000100100", 
    122 => "00111010001001000000100100", 123 => "00111011000110010000100101", 
    124 => "00111100000100000000100110", 125 => "00111101000010010000100111", 
    126 => "00111110000001000000101000", 127 => "00111111000000010000101001", 
    128 => "01000000000000000000101010", 129 => "01000001000000010000101011", 
    130 => "01000010000001000000101100", 131 => "01000011000010010000101101", 
    132 => "01000100000100000000101110", 133 => "01000101000110010000101111", 
    134 => "01000110001001000000110000", 135 => "01000111001100010000110010", 
    136 => "01001000010000000000110011", 137 => "01001001010100010000110100", 
    138 => "01001010011001000000110101", 139 => "01001011011110010000110110", 
    140 => "01001100100100000000110111", 141 => "01001101101010010000111001", 
    142 => "01001110110001000000111010", 143 => "01001111111000010000111011", 
    144 => "01010001000000000000111100", 145 => "01010010001000010000111110", 
    146 => "01010011010001000000111111", 147 => "01010100011010010001000000", 
    148 => "01010101100100000001000001", 149 => "01010110101110010001000011", 
    150 => "01010111111001000001000100", 151 => "01011001000100010001000110", 
    152 => "01011010010000000001000111", 153 => "01011011011100010001001000", 
    154 => "01011100101001000001001010", 155 => "01011101110110010001001011", 
    156 => "01011111000100000001001101", 157 => "01100000010010010001001110", 
    158 => "01100001100001000001010000", 159 => "01100010110000010001010001", 
    160 => "01100100000000000001010011", 161 => "01100101010000010001010100", 
    162 => "01100110100001000001010110", 163 => "01100111110010010001011000", 
    164 => "01101001000100000001011001", 165 => "01101010010110010001011011", 
    166 => "01101011101001000001011101", 167 => "01101100111100010001011110", 
    168 => "01101110010000000001100000", 169 => "01101111100100010001100010", 
    170 => "01110000111001000001100011", 171 => "01110010001110010001100101", 
    172 => "01110011100100000001100111", 173 => "01110100111010010001101001", 
    174 => "01110110010001000001101011", 175 => "01110111101000010001101101", 
    176 => "01111001000000000001101110", 177 => "01111010011000010001110000", 
    178 => "01111011110001000001110010", 179 => "01111101001010010001110100", 
    180 => "01111110100100000001110110", 181 => "01111111111110010001111000", 
    182 => "10000001011001000001111010", 183 => "10000010110100010001111100", 
    184 => "10000100010000000001111110", 185 => "10000101101100010010000000", 
    186 => "10000111001001000010000010", 187 => "10001000100110010010000101", 
    188 => "10001010000100000010000111", 189 => "10001011100010010010001001", 
    190 => "10001101000001000010001011", 191 => "10001110100000010010001101", 
    192 => "10010000000000000010010000", 193 => "10010001100000010010010010", 
    194 => "10010011000001000010010100", 195 => "10010100100010010010010110", 
    196 => "10010110000100000010011001", 197 => "10010111100110010010011011", 
    198 => "10011001001001000010011101", 199 => "10011010101100010010100000", 
    200 => "10011100010000000010100010", 201 => "10011101110100010010100101", 
    202 => "10011111011001000010100111", 203 => "10100000111110010010101010", 
    204 => "10100010100100000010101100", 205 => "10100100001010010010101111", 
    206 => "10100101110001000010110001", 207 => "10100111011000010010110100", 
    208 => "10101001000000000010110111", 209 => "10101010101000010010111001", 
    210 => "10101100010001000010111100", 211 => "10101101111010010010111111", 
    212 => "10101111100100000011000001", 213 => "10110001001110010011000100", 
    214 => "10110010111001000011000111", 215 => "10110100100100010011001010", 
    216 => "10110110010000000011001101", 217 => "10110111111100010011001111", 
    218 => "10111001101001000011010010", 219 => "10111011010110010011010101", 
    220 => "10111101000100000011011000", 221 => "10111110110010010011011011", 
    222 => "11000000100001000011011110", 223 => "11000010010000010011100001", 
    224 => "11000100000000000011100100", 225 => "11000101110000010011100111", 
    226 => "11000111100001000011101010", 227 => "11001001010010010011101101", 
    228 => "11001011000100000011110001", 229 => "11001100110110010011110100", 
    230 => "11001110101001000011110111", 231 => "11010000011100010011111010", 
    232 => "11010010010000000011111110", 233 => "11010100000100010100000001", 
    234 => "11010101111001000100000100", 235 => "11010111101110010100001000", 
    236 => "11011001100100000100001011", 237 => "11011011011010010100001110", 
    238 => "11011101010001000100010010", 239 => "11011111001000010100010101", 
    240 => "11100001000000000100011001", 241 => "11100010111000010100011100", 
    242 => "11100100110001000100100000", 243 => "11100110101010010100100011", 
    244 => "11101000100100000100100111", 245 => "11101010011110010100101011", 
    246 => "11101100011001000100101110", 247 => "11101110010100010100110010", 
    248 => "11110000010000000100110110", 249 => "11110010001100010100111010", 
    250 => "11110100001001000100111101", 251 => "11110110000110010101000001", 
    252 => "11111000000100000101000101", 253 => "11111010000010010101001001", 
    254 => "11111100000001000101001101", 255 => "11111110000000010101010001" );


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

memory_access_guard_1: process (address1) 
begin
      address1_tmp <= address1;
--synthesis translate_off
      if (CONV_INTEGER(address1) > AddressRange-1) then
           address1_tmp <= (others => '0');
      else 
           address1_tmp <= address1;
      end if;
--synthesis translate_on
end process;

p_rom_access: process (clk)  
begin 
    if (clk'event and clk = '1') then
        if (ce0 = '1') then 
            q0 <= mem(CONV_INTEGER(address0_tmp)); 
        end if;
        if (ce1 = '1') then 
            q1 <= mem(CONV_INTEGER(address1_tmp)); 
        end if;
    end if;
end process;

end rtl;

