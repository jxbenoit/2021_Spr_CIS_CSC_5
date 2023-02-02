#include<iostream>
#include<string>
#include<bitset>
#include<sstream>
#include<iomanip>
#include<vector>
#include<math.h>
#include<string.h>  //strcpy
#include<cstdlib>   //strtol

using namespace std;

union double_to_chars {
    double d;
    unsigned char c[8];
};

struct SHA_UInts {
    unsigned int a, b, c, d, e, f, g, h;
    unsigned int temp1, temp2, maj, ch, S0, S1;
};

uint32_t getFractionalPart(double value);
string AsHexString( double d );
void RotateRight( char *w, int n );
void ShiftRight( char *w, int n );
int XOR( char *w1, char *w2 );
void Add( char *w1, char *w2 );
void PrintAsBits( unsigned int I );
unsigned int uintRotateRight( unsigned int val, int n );
unsigned int ConvertToUINT( char *Bits );
void Compress( unsigned int h_[], unsigned int k[], unsigned int w[],
               SHA_UInts &vals );
void Decompress( SHA_UInts vals, unsigned int h_[], unsigned int k[],
                 unsigned int w[] );

int main(int argc, char** argv) {
  string s;
  cout << "Enter text: ";
  getline( cin, s );

  //STEP 1:
  int orig_bit_len = s.length() * 8; //Needed for later

  //In binary
  stringstream bitstream;
  for( int i = 0; i < s.size(); i++ ) {
        char c = s[i];
        bitset<8> b(c);
        bitstream << b;
  }
  string bits;
  getline( bitstream, bits );

  bits = bits + '1';

  //Pad with 0's until data is multiple 0f 512, less 64.
  int pad_size = 512;
  int bits_size = bits.length();
  while( pad_size < bits_size )
      pad_size += 512;
  int num_zeros_to_add = pad_size - bits_size - 64;

  stringstream ss;
  ss << bits << setw(num_zeros_to_add) << setfill('0') << "";
  bitset<64> big_end( (unsigned long) orig_bit_len );
  ss << big_end;
  getline( ss, bits );

  //STEP 2:
  //Note: Only first 8 primes needed here, but first 64 primes are needed
  //      in STEP 3.
  int primes[] = {   2,   3,   5,   7,  11,  13,  17,  19,
                    23,  29,  31,  37,  41,  43,  47,  53,
                    59,  61,  67,  71,  73,  79,  83,  89,
                    97, 101, 103, 107, 109, 113, 127, 131,
                   137, 139, 149, 151, 157, 163, 167, 173,
                   179, 181, 191, 193, 197, 199, 211, 223,
                   227, 229, 233, 239, 241, 251, 257, 263,
                   269, 271, 277, 281, 283, 293, 307, 311
                  };
  unsigned int h_[8];

  for( int i = 0; i < 8; i++ ) {
      double d = sqrt( primes[i] );

      uint32_t frac = getFractionalPart( d );
      h_[i] = frac;
  }

  //STEP 3:
  unsigned int k[64];
  for( int i = 0; i < 64; i++ ) {
      double d = pow( primes[i], 1/3.0 );

      uint32_t frac = getFractionalPart( d );
      k[i] = frac;
  }
    
  //STEP 4: Chunk Loop
  //For the example, we only have one chunk.
    
  //STEP 5: Create Message Schedule
  bits.append( 48 * 32, '0' );
  
  unsigned int w[64];
  for( int i=0; i< 64; i++ )
    w[i] = ConvertToUINT( &bits[i*32] );

  for( int i=16; i<64; i++ ) {
    char w1[33],w2[33],w3[33];
    strncpy( w1, &bits[(i-15)*32], 32 );
    w1[32] = 0;
    RotateRight( w1, 7 );

    strncpy( w2, &bits[(i-15)*32], 32 );  
    w2[32] = 0;
    RotateRight( w2, 18 );

    strncpy( w3, &bits[(i-15)*32], 32 );  
    w3[32] = 0;
    ShiftRight( w3, 3 );

    char s0[33];
    strcpy( s0, w1 );
    XOR( s0, w2 );
    XOR( s0, w3 );
 
    strncpy( w1, &bits[(i-2)*32], 32 );
    w1[32] = 0;
    RotateRight( w1, 17 );

    strncpy( w2, &bits[(i-2)*32], 32 );
    w2[32] = 0;
    RotateRight( w2, 19 );

    strncpy( w3, &bits[(i-2)*32], 32 );  
    w3[32] = 0;
    ShiftRight( w3, 10 );

    char s1[33];
    strcpy( s1, w1 );
    XOR( s1, w2 );
    XOR( s1, w3 ); 
 
    strncpy( w1, &bits[(i-16)*32], 32 );
    w1[32] = 0;
    strncpy( w2, &bits[(i-7)*32], 32 );
    w2[32] = 0;

    Add( &bits[i*32], s1 );
    Add( &bits[i*32], &bits[(i-7)*32] );
    Add( &bits[i*32], s0 );
    Add( &bits[i*32], &bits[(i-16)*32] );

    w[i] = ConvertToUINT( &bits[i*32] );

    //Debug info.
    char dw[33];
    strncpy( dw, &bits[i*32], 32 );
    dw[32] = 0;
  }

  //STEP 6 - Compression
  cout << "STEP 6:" << endl;
  SHA_UInts vals;
  Compress( h_, k, w, vals );

  Decompress( vals, h_, k, w );

  //STEP 7 - Modify Final Values
  h_[0] += vals.a;
  h_[1] += vals.b;
  h_[2] += vals.c;
  h_[3] += vals.d;
  h_[4] += vals.e;
  h_[5] += vals.f;
  h_[6] += vals.g;
  h_[7] += vals.h;

  //STEP 8 - Concatenate Final Hash
  for( int i = 0; i < 8; i++ )
      cout << hex << h_[i];
  cout << endl;
  
  return 0;
}

/*getFractionalPart
  See https://stackoverflow.com/questions/42689193/hexadecimal-representation-
      of-double-fractional-part-for-sha-256
  and https://en.wikipedia.org/wiki/Double-precision_floating-point_format
*/
uint32_t getFractionalPart(double value)
{
  uint32_t retValue = 0;

  for ( uint8_t i = 0; i < 8; i++ ) {
    value = value - floor(value);
    retValue <<= 4;
    value *= 16;
    int nibble = static_cast<int>( floor(value) );
    retValue += nibble;
  }

  return retValue;
}

string AsHexString( double d )
{
  double_to_chars sr;
  sr.d = d;

  stringstream ss;
  ss << hex
     << setw(2) << setfill('0') << static_cast<short>(sr.c[7]) << " "
     << setw(2) << setfill('0') << static_cast<short>(sr.c[6]) << " "
     << setw(2) << setfill('0') << static_cast<short>(sr.c[5]) << " "
     << setw(2) << setfill('0') << static_cast<short>(sr.c[4]) << " "
     << setw(2) << setfill('0') << static_cast<short>(sr.c[3]) << " "
     << setw(2) << setfill('0') << static_cast<short>(sr.c[2]) << " "
     << setw(2) << setfill('0') << static_cast<short>(sr.c[1]) << " "
     << setw(2) << setfill('0') << static_cast<short>(sr.c[0]);

  string s;
  getline( ss, s );

  return s;
}

void RotateRight( char *w, int n ) {
  for( int i=0; i < n; i++ ) {
    char bit = w[31];
    for( int j=31; j > 0; j-- )
      w[j] = w[j-1];
    w[0] = bit;
  }
}

void ShiftRight( char *w, int n ) {
  for( int i=0; i < n; i++ ) {
    for( int j=31; j > 0; j-- )
      w[j] = w[j-1];
    w[0] = '0';
  }
}

int XOR( char *w1, char *w2 ) {
  int carry = 0;
  for( int i=31; i >= 0; i-- ) {
    w1[i] = (w1[i]=='0') ?
           ((w2[i]=='0') ? '0' : '1') :
           ((w2[i]=='0') ? '1' : '0');
    carry = (w1[i]=='1' && w2[i]=='1') ?
           1 : 0;
  }

  return carry;
}

void Add( char *w1, char *w2 ) {
  //XOR(w1, w2);
  int carry = 0;
  for( int i=31; i >= 0; i-- ) {
    if( ! carry ) {
      if( w1[i] == '0' ) {
        if( w2[i] == '0' )
          w1[i] = '0';
        else w1[i] = '1';
      }
      else {
        if( w2[i] == '0' )
          w1[i] = '1';
        else {
          w1[i] = '0';
          carry = 1;
        }
      }
    }
    else {  //carry is 1
      if( w1[i] == '0' ) {
        if( w2[i] == '0' ) {
          w1[i] = '1';
          carry = 0;
        }
        else w1[i] = '0';
      }
      else {
        if( w2[i] == '0' )
          w1[i] = '0';
        else w1[i] = '1';
      }        
    }
  }
}

unsigned int uintRotateRight( unsigned int val, int n ) {
  return ( (val>>n) | (val<<(32-n)) );
}

void PrintAsBits( unsigned int I ) {
  bitset<32> x(I);
  cout << x;
}

unsigned int ConvertToUINT( char *Bits ) {
    unsigned int val = 0;
    unsigned int place = 1;
    for( int i = 31; i >= 0; i-- ) {
      val |= (Bits[i] == '1') ? place : 0;
      place = place << 1;
    }

    return val;
}

void Compress( unsigned int h_[], unsigned int k[], unsigned int w[],
               SHA_UInts &vals ) {
  vals.a = h_[0];
  vals.b = h_[1];
  vals.c = h_[2];
  vals.d = h_[3];
  vals.e = h_[4];
  vals.f = h_[5];
  vals.g = h_[6];
  vals.h = h_[7];

  for( int i = 0; i < 64; i++ ) {
    if(i>60) cout << dec << "i=" << i << endl;
    unsigned int rr1 = uintRotateRight( vals.e, 6 );
    unsigned int rr2 = uintRotateRight( vals.e, 11 );
    unsigned int rr3 = uintRotateRight( vals.e, 25 );
    vals.S1 = rr1 xor rr2 xor rr3;

    unsigned int ch_a = (vals.e & vals.f);
    unsigned int ch_b = vals.e xor 0b11111111111111111111111111111111;
    unsigned int ch_c = (ch_b & vals.g);
    vals.ch = ch_a xor ch_c;

    //cout << "h0=(";  PrintAsBits( vals.h );  cout << ")" << endl;
    vals.temp1 = vals.h + vals.S1 + vals.ch + k[i] + w[i];

    rr1 = uintRotateRight( vals.a, 2 );
    rr2 = uintRotateRight( vals.a, 13 );
    rr3 = uintRotateRight( vals.a, 22 );
    vals.S0 = rr1 xor rr2 xor rr3;

    vals.maj = (vals.a & vals.b) xor (vals.a & vals.c) xor
                       (vals.b & vals.c);

    vals.temp2 = vals.S0 + vals.maj;

    if(i>60) {
      cout << "A f=" << hex << vals.f << endl;
      cout << "A g=" << hex << vals.g << endl;
      cout << "A h=" << hex << vals.h << endl;
    }
  
    vals.h = vals.g;
 
    if(i>60) {
      cout << "B h=" << hex << vals.h << endl;
    }
  
    vals.g = vals.f;
    vals.f = vals.e;
    vals.e = vals.d + vals.temp1;
    vals.d = vals.c;
    vals.c = vals.b;
    vals.b = vals.a;
    vals.a = vals.temp1 + vals.temp2;
   
    //if(i>60) ShowVars( vals );

    if(i>60) {
      cout << "C h=" << hex << vals.h << endl;
    }
  }
}

void Decompress( SHA_UInts vals, unsigned int h_[], unsigned int k[],
                 unsigned int w[] ) {
  cout << "Decompress:" << endl;

  for( int i = 63; i >= 60; i-- ) {
    if(i>60) {
      cout << "C h=" << hex << vals.h << endl;
    }
    //if(i>60) ShowVars( vals, true );

    vals.a = vals.b;
    vals.b = vals.c;
    vals.c = vals.d;
    vals.d = vals.e - vals.temp1;
    vals.e = vals.f;
    vals.f = vals.g;
    vals.g = vals.h;

    if(i>60) {
      cout << "B h=" << hex << vals.h << endl;
    }

    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //Try to reverse solve for h    
    unsigned int a0;
    unsigned int b0;
    unsigned int c0;
    unsigned int d0;
    unsigned int e0;
    unsigned int f0;
    unsigned int g0;

    vals.h = vals.temp1 - vals.S1 - vals.ch - k[i] - w[i];
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    if(i>60) {
      cout << "A h=" << hex << vals.h << endl;
      cout << "A g=" << hex << vals.g << endl;
      cout << "A f=" << hex << vals.f << endl;
    }
    
    vals
 
    a0 = vals.b;
    b0 = vals.c;
    c0 = vals.d;
    d0 = vals.e;
    e0 = vals.f;
    f0 = vals.g;
    g0 = vals.h;

    unsigned int rr1 = uintRotateRight( a0, 2 );
    unsigned int rr2 = uintRotateRight( a0, 13 );
    unsigned int rr3 = uintRotateRight( a0, 22 );
    vals.S0 = rr1 xor rr2 xor rr3;

    vals.maj = (a0 & b0) xor (a0 & c0) xor (b0 & c0);

    vals.temp2 = vals.S0 + vals.maj;

    rr1 = uintRotateRight( e0, 6 );
    rr2 = uintRotateRight( e0, 11 );
    rr3 = uintRotateRight( e0, 25 );
    vals.S1 = rr1 xor rr2 xor rr3;

    unsigned int ch_a = (e0 & f0);
    unsigned int ch_b = e0 xor 0b11111111111111111111111111111111;
    unsigned int ch_c = (ch_b & g0);
    vals.ch = ch_a xor ch_c;

    //cout << "h0=(";  PrintAsBits( h );  cout << ")" << endl;
    vals.temp1 = vals.h + vals.S1 + vals.ch + k[i] + w[i];

    if(i>60) cout << dec << "i=" << i << endl;
  }
}

void ShowVars( SHA_UInts vals, bool reverse ) {
  if( ! reverse ) {
    cout << "a=";  PrintAsBits( vals.a );  cout << endl;
    cout << "b=";  PrintAsBits( vals.b );  cout << endl;
    cout << "c=";  PrintAsBits( vals.c );  cout << endl;
    cout << "d=";  PrintAsBits( vals.d );  cout << endl;
    cout << "e=";  PrintAsBits( vals.e );  cout << endl;
    cout << "f=";  PrintAsBits( vals.f );  cout << endl;
    cout << "g=";  PrintAsBits( vals.g );  cout << endl;
    cout << "h=";  PrintAsBits( vals.h );  cout << endl;
    cout << "S1=";  PrintAsBits( vals.S1 );  cout << " (" << vals.S1 << ")" << endl;
    cout << "ch=";  PrintAsBits( vals.ch );  cout << " (" << vals.ch << ")" << endl;
    cout << "temp1=";  PrintAsBits( vals.temp1 );  cout << " (" << vals.temp1 << ")" << endl;
    cout << "S0=";  PrintAsBits( vals.S0 );  cout << " (" << vals.S0 << ")" << endl;
    cout << "maj=";  PrintAsBits( vals.maj );  cout << " (" << vals.maj << ")" << endl;
    cout << "temp2=";  PrintAsBits( vals.temp2 );  cout << " (" << vals.temp2 << ")" << endl;
  }
  else {
    cout << "temp2=";  PrintAsBits( vals.temp2 );  cout << " (" << vals.temp2 << ")" << endl;
    cout << "maj=";  PrintAsBits( vals.maj );  cout << " (" << vals.maj << ")" << endl;
    cout << "S0=";  PrintAsBits( vals.S0 );  cout << " (" << vals.S0 << ")" << endl;
    cout << "temp1=";  PrintAsBits( vals.temp1 );  cout << " (" << vals.temp1 << ")" << endl;
    cout << "ch=";  PrintAsBits( vals.ch );  cout << " (" << vals.ch << ")" << endl; 
    cout << "S1=";  PrintAsBits( vals.S1 );  cout << " (" << vals.S1 << ")" << endl;
    cout << "h=";  PrintAsBits( vals.h );  cout << endl;
    cout << "g=";  PrintAsBits( vals.g );  cout << endl;
    cout << "f=";  PrintAsBits( vals.f );  cout << endl;
    cout << "e=";  PrintAsBits( vals.e );  cout << endl;
    cout << "d=";  PrintAsBits( vals.d );  cout << endl;
    cout << "c=";  PrintAsBits( vals.c );  cout << endl;
    cout << "b=";  PrintAsBits( vals.b );  cout << endl;
    cout << "a=";  PrintAsBits( vals.a );  cout << endl;
   }
 }