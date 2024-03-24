#include "pow.hpp"

/*
 * p= 179769313486231590772930519078902473361797697894230657273430081157732675805500963132708477322407536021120113879871393357658789768814416622492847430639474124377767893424865485276302219601246094119453082952085005768838150682342462881473913110540827237163350510684586298239947245938479716304835356329624224137859
 * q=152379194905679248584139201744286431663274312896667401414974604257425570946241723112153673017992850464436760655272032014909771084338214975784861855742836919833600760640004836771691982443453635043338771387495588498913061742536356419244258215214559494626029610546721045478549545372994408254566479036839453206439
 * pq=27393103257778636656013778278281939363389700397419532985525806837115170675638339579293972360781990004637036103166119041735755803563983183159360907539224124286564802871338187355441147419462345095896172796746742354006497181419467323536999552669928013193935883985229439967010719264359464795668704763597106539393093132538372888849557206276190930314018831887225962960700451465965420795609984604188681859959909078491372872840936007512104638177352746099094689226719754626897914879157963178098882584740752082431475503492795227881372952432161446246421413722505500106661935514712400670043309016960160850926466580417357922474101
 */

int main(void)
{
  mon para;

  para.nbit=2048;
  // nr 17954464523682603969815309358094063589316591455729718778902571495360611031353337854014783369215838331626263957625783235497711239651235728120801265421086008107917354732416533331067880297970292159197356954182490655068615466489974963053719226537029192292560294120969127595103625141504451897779273996559249034021946759602633634970751873733819967769157606831980900774059544198827348789721996569977122690380899427501886198087698079925172866780836188178153234219623872489346756910466146745891065388105715177504185912146443842429623211788535084164864123454334402213758381018001604762429864240394557238863573463390604011604003,
  para.nr.buf[0]=ap_uint<256>("1000111000111010000011001010010001111010110011101000010010000010110000111111011100100010110101110111110111000101110001011101111000100000011100100100101000101111000101111101010001011001010111000011010110011011100000000101111101010000001010111101011010000100",2);
  para.nr.buf[1]=ap_uint<256>("0001001111000111011101010000010101001100110101010100110000100110010111010010100111000100111001001000111011100000000000111011011010111011100111100001000111011110001011100110101011110000111010011011100000101100010100010001100110011011101011010110100100111100",2);
  para.nr.buf[2]=ap_uint<256>("0100110010001010100000110101100110001011000111111110011110011111011000101101110101010010000001101100000010101110000101111000010101101000110010011101100000101001010000111010100100110000100010111011111001000111101111101100001101101000110001111100000111011011",2);
  para.nr.buf[3]=ap_uint<256>("1110000011110000000010101011111110001101111101111100011000100001010000000010110110011011010101010101100010010101000010010001101110010010000110000000110011010010010100101011010101101001100010000101000010100011000001001000101000111100001111001110000100000100",2);
  para.nr.buf[4]=ap_uint<256>("0001000011000110010101001101100001110110110001001110111001110000000100000100011101100110001110011111100000010111011110110110011010110001100000110100011111101111101010101010011000010000100101100101010110101101010010110011010100011010010001111110001010010100",2);
  para.nr.buf[5]=ap_uint<256>("0011000110010101101000010110110011101011101111011101111100110001110011101101110001100111000010110101101110111000110100110110111010111010011000011110100101111110110100001011010100110011010011100110111011011101000000101001011111100001011010111001000011000101",2);
  para.nr.buf[6]=ap_uint<256>("1111110100101011111001110110000010010100001100011110000111000111010110011111011010010001000101110010011111000101111001010100001101011111000011001000001010110000110001101101110011011101111110000011010111000100100110101001110000010110000111011111001110111110",2);
  para.nr.buf[7]=ap_uint<256>("1011010010011111001001111111011111010001011100111110111100001010111100100101010010111110000101010110110001011111001110100000111101110100001110010001000101011000110111010100011101111100000111101011100010001011000010010100101010110110100100011000100000100011",2);

  para.modp.buf[0]=ap_uint<256>("1101100011111110110000111110000111011001101101000010111111001101001101011110111010001110101111101101011001110000111111101010010010001000100100111111100010011011111010000111111011001110010100000010010100001001100101111011100001111011110000100011011010001011",2);
  para.modp.buf[1]=ap_uint<256>("1001111001001101010000001110110110111011000001011110101010011100110011000010010111101100100001000010000001000101011101011100110010111011110000010111111101001111110111000100010100010110110000101110011111101010101011010100100100001010011100001010111100010110",2);
  para.modp.buf[2]=ap_uint<256>("0010110000011011000011001011111101100010001010111011110001000010001100111110110011001001001001111001000110000110010010110011000011000100000110111101000110001011001000000100110110111101000011000111111100000111000001001000111001110111111110011111100001001000",2);
  para.modp.buf[3]=ap_uint<256>("0010001001110011111110101110010001111101000000100110010100010101000101100100011101011010100100010001000011010111001001011000111000000110011110000010010111110110000000001110110001111111111001010110110100110000101000010011001100001011110001110010100111001000",2);
  para.modp.buf[4]=ap_uint<256>("0000011111100110000000000100010111001111100101000001000001101110011101100011000010001001010101001001110111001111100101110100001100001011101010010110111110011000111101101000000000110011010011010000011100011000000101000101111011011000110011110000000010101110",2);
  para.modp.buf[5]=ap_uint<256>("1001110000001010000101010001110010111111110111000100011111010100110000110100000100001111110111010000111001110110111000010011101110010111000000101100010110010110010000011000100000101011100011001000001001110001001111100111010100111001000001111100010010110000",2);
  para.modp.buf[6]=ap_uint<256>("1100011111110001000001001011001110010011110110011101101001001000011010111011110100111110011000101000010001001110110110110111110010010001110111110101000001110010001000110100000111010110011000110000111010100000011100011101011101011000110110101001110100101110",2);
  para.modp.buf[7]=ap_uint<256>("1000100101001111001010111110010111111101000000111110001111110110111101010011100001111010010111010100110001100011010100111011101000111111110001110101100011100100010100100000010100111101010000010100000100100100111000110011011010010101001110001001100001110101",2);

	uint2048_t x,y,z;
	uint4096_t zz;

	x.buf[0]=ap_uint<256>("1110110101010100110111110000000010110010100111000010011001100011000011111010111111011110011010100011000111010010101111101011000101101101011111100011011110011101010101110001000000100001101001010001110010000010010010010101110101000111101011000001010000110100",2);
  x.buf[1]=ap_uint<256>("0000001110000111010001011010111011000111101011111111101011110101110101001111100100101111101011111000111001001110111001100001110000000101111111000111100000000100000101110010111010010111110100110000100110001111111011110010101001111011001011100100111101001001",2);
  x.buf[2]=ap_uint<256>("1111011111111000001101100110110000001011011000010000010100011011101000110100110011110011011111011011000111100100110011101111101011011100011011110101110110001110101111010110101101010111011010001010000010010001100001101111000010000001100110000100011101101100",2);
  x.buf[3]=ap_uint<256>("1111010011101001110010010011101010100101110101110010101001011011101100110010010101001010001001011001010100010101011100101011011010010011101101011010100011000011000011010100000100010100101000100010010011011101000000000011110011110001001100110100101010001010",2);
  x.buf[4]=ap_uint<256>("1011011101000100111010101011011001110100010010011011010000011011001101100000000110101001110000010111111110000000100101011001010101010101010101100110001101011100110111100010111011110110011101011011010110110011101111011011110111111110000011111110101100101011",2);
  x.buf[5]=ap_uint<256>("1111100011010001100100010101101011100010100111001010010100001111111100000100010000100000000110011010111010111111100111110110111010010110110101111111111010111100011011111110000111101110001011110011001111000101111010111011100001011001001000001110011101000110",2);
  x.buf[6]=ap_uint<256>("1101000110000110011000000101101011100000101010110011000000000010010010010011100010001011110100001100001000011011101010001110101011011010111000100011110011000010001101001110001000101010110100011011011001011000000101011111010011110010010000010110101011110010",2);
  x.buf[7]=ap_uint<256>("1011100010011010111010011111101000110100111011000110000110111111111111011010000111001011101111101101010111001010110111111100101001011010110111000111111101000111100111101110100111000001000101110011101111001110011011111111010010110100001001010100000010001111",2);


y.buf[0]="107348099375920676904089524633530064712722804864547103118197496470222052004916";
y.buf[1]="1595943832053069826775139925756361211228704007617209621855906345808798043977";
y.buf[2]="112159827279307150886706599923800279211480347761815772750045607818564086548332";
y.buf[3]="110777399252568015972217092174987635518544872353142320820707269624871485917834";
y.buf[4]="110777399252568015972217092174987635518544872353142320820707269624871485917834";
y.buf[5]="110777399252568015972217092174987635518544872353142320820707269624871485917834";
y.buf[6]="110777399252568015972217092174987635518544872353142320820707269624871485917834";
y.buf[7]="83499273439755836650252582616698179897213191214267277135422013856843087298703";

//addT(z.buf,x.buf,y.buf);
z=mul_fp(x,y,para);

//z=sliding_window(x,y,para);
//binary(z,x,y,para);

for(int i=0;i<8;i++){
  std::cout<<z.buf[i]<<std::endl;
}


/*
mul(zz,x,y);
for(int i=0;i<16;i++){
  std::cout<<zz.buf[i]<<std::endl;
}
*/

	return 0;
}
