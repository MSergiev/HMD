#ifndef VECTOR_H
#define VECTOR_H

#define STR_LEN 100
#define PI 3.141526

typedef unsigned char uint8;

// Swap two elements
inline void swap( float& a, float& b ) {
	float tmp = a; 
	a=b; 
	b=tmp; 
}

// Convert degrees to radians
float rad( float deg ) {
    return deg*PI/180.0f;
}

// Map a value from one range to another
float mapTo( float val, float in, float out, float nIn, float nOut ) {
    float in_min, in_max, out_min, out_max;
    bool in_rev = (in<out), out_rev = (nIn<nOut);
    
    if(in_rev) { in_min = in; in_max = out; } else { in_min = out; in_max = in; }
    if(out_rev) { out_min = nIn; out_max = nOut; } else { out_min = nOut; out_max = nIn; }
    
    float in_len = in_max - in_min;
    float out_len = out_max - out_min;
    
    float tmp = val;
    tmp -= in_min;
    if(in_rev) tmp = in_len - tmp;
    tmp /= in_len;
    tmp *= out_len;
    if(out_rev) tmp = out_len - tmp;
    tmp += out_min;
    
    if(tmp < out_min) tmp = out_min;
    if(tmp > out_max) tmp = out_max;
    
    return tmp;
}


//////////////////////////////////////////////////

/** VEC2 */
struct vec2 {
  // Constant size
  static const uint8 size = 2;
    
    // Array
	float vec[size];

    // Default constructor
	vec2() {
		memset( vec, 0, sizeof(vec) );	
	}

	// Braced constructor
	vec2( float x, float y ) { 
		vec[0] = x;	
		vec[1] = y;
	}
	
	// Uniform constructor
	vec2( float a ) { 
		vec[0] = a;
		vec[1] = a;
	}
	
	// Copy operator
	void operator= ( const vec2& a ) { 
		memcpy(vec,a.vec,sizeof(vec)); 
	}

	// Square brace operator
	float& operator[] ( uint8 index ) { 
		return vec[index]; 
	}
	
	// Const square brace operator
	float operator[] ( uint8 index ) const { 
		return vec[index]; 
	}

	// Addition operator
	vec2& operator+= ( const vec2& a ) { 
		for( int i = 0; i < size; ++i ) {
			vec[i]+=a.vec[i];
		}
		return *this;
	}

	// Subtraction operator
	vec2& operator-= ( const vec2& a ) { 
		for( int i = 0; i < size; ++i ) {
			vec[i]-=a.vec[i];
		}
		return *this;
	}

	// Multiplication operator
	float operator*= ( const vec2& a ) {
		float dot = 0;
		for( int i = 0; i < size; ++i ) {
			dot += vec[i]*a.vec[i];
		}	
		return dot;
  }

  // Multiplication operator
  vec2& operator*= ( const float a ) {
		for( int i = 0; i < size; ++i ) {
			vec[i]*=a;
		}	
		return *this;
  }

  // Division operator
  vec2& operator/= ( const float a ) {
		for( int i = 0; i < size; ++i ) {
			vec[i]/=a;
		}	
		return *this;
  }

  // Vector length
	float length() {
		return sqrt(vec[0]*vec[0] + vec[1]*vec[1]);
	}

	// Normalized vector
	vec2& normalize() {
		*this/=length();
		return *this;	
	}
};

// Binary addition operator
vec2 operator+ ( vec2 a, const vec2& b ) {
		return a+=b;
}

// Binary subtraction operator
vec2 operator- ( vec2 a, const vec2& b ) {
		return a-=b;
}

// Binary multiplication operator
float operator* ( vec2 a, const vec2& b ) {
	return a*=b;
}

// Binary multiplication operator
vec2 operator* ( vec2 a, const float b ) {
	return a*=b;
}


//////////////////////////////////////////////////

/** VEC3 */
struct vec3 {
  static const uint8 size = 3;
    
	float vec[size];

	vec3() {
		memset( vec, 0, sizeof(vec) );	
	}

	vec3( float x, float y, float z ) { 
		vec[0] = x;	
		vec[1] = y;	
		vec[2] = z;	
	}
	
	vec3( float a ) { 
		vec[0] = a;	
		vec[1] = a;	
		vec[2] = a;	
	}
	
	void operator= ( const vec3& a ) { 
		memcpy(vec,a.vec,sizeof(vec)); 
	}

	float& operator[] ( uint8 index ) { 
		return vec[index]; 
	}

	float operator[] ( uint8 index ) const { 
		return vec[index]; 
	}

	vec3& operator+= ( const vec3& a ) { 
		for( int i = 0; i < size; ++i ) {
			vec[i]+=a.vec[i];
		}
		return *this;	
	}

	vec3& operator-= ( const vec3& a ) { 
		for( int i = 0; i < size; ++i ) {
			vec[i]-=a.vec[i];
		}
		return *this;	
	}

	float operator*= ( const vec3& a ) {
		float dot = 0;
		for( int i = 0; i < size; ++i ) {
			dot += vec[i]*a.vec[i];
		}	
		return dot;
  }
   	
	vec3& operator*= ( const float a ) {
		for( int i = 0; i < size; ++i ) {
			vec[i] *= a;
		}	
		return *this;
  }

  vec3& operator/= ( const float a ) {
		for( int i = 0; i < size; ++i ) {
			vec[i]/=a;
		}	
		return *this;
  }

	vec3& operator&= ( const vec3& a ) {
		vec3 v;
		v[0] = vec[1]*a.vec[2] - vec[2]*a.vec[1];
		v[1] = vec[2]*a.vec[0] - vec[0]*a.vec[2];
		v[2] = vec[0]*a.vec[1] - vec[1]*a.vec[0];
		*this = v;
		return *this;
	}
	
	float length() {
		return sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);
	}

	vec3& normalize() {
		*this/=length();
		return *this;	
	}
};

vec3 operator+ ( vec3 a, const vec3& b ) {
		return a+=b;
}

vec3 operator- ( vec3 a, const vec3& b ) {
		return a-=b;
}

float operator* ( vec3 a, const vec3& b ) {
	return a*=b;
}

vec3 operator* ( vec3 a, const float b ) {
	return a*=b;
}

vec3 operator& ( vec3 a, const vec3& b ) {
	return a&=b;
}

//////////////////////////////////////////////////

/** VEC4 */
struct vec4 {
  static const uint8 size = 4;
    
	float vec[size];

	vec4() {
		memset( vec, 0, sizeof(vec) );	
	}

	vec4( float x, float y, float z, float w ) { 
		vec[0] = x;	
		vec[1] = y;	
		vec[2] = z;	
		vec[3] = w;	
	}
	
	vec4( float a ) { 
		vec[0] = a;	
		vec[1] = a;	
		vec[2] = a;	
		vec[3] = a;	
	}
	
	void operator= ( const vec4& a ) { 
		memcpy(vec,a.vec,sizeof(vec)); 
	}

	float& operator[] ( uint8 index ) { 
		return vec[index]; 
	}
	
	float operator[] ( uint8 index ) const { 
		return vec[index]; 
	}

	vec4& operator+= ( const vec4& a ) { 
		for( int i = 0; i < size; ++i ) {
			vec[i]+=a.vec[i];
		}
		return *this;	
	}

	vec4& operator-= ( const vec4& a ) { 
		for( int i = 0; i < size; ++i ) {
			vec[i]-=a.vec[i];
		}
		return *this;	
	}

	float operator*= ( const vec4& a ) {
		float dot = 0;
		for( int i = 0; i < size; ++i ) {
			dot += vec[i]*a.vec[i];
		}
		return dot;
  }
   	
  vec4& operator*= ( const float a ) {
		for( int i = 0; i < size; ++i ) {
			vec[i]*=a;
		}	
		return *this;
  }
   	
  vec4& operator/= ( const float a ) {
		for( int i = 0; i < size; ++i ) {
			vec[i]/=a;
		}	
		return *this;
  }

	float length() {
		return sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2] + vec[3]*vec[3]);
	}

	vec4& normalize() {
		*this/=length();
		return *this;	
	}
};

vec4 operator+ ( vec4 a, const vec4& b ) {
		return a+=b;
}

vec4 operator- ( vec4 a, const vec4& b ) {
		return a-=b;
}

float operator* ( vec4 a, const vec4& b ) {
	return a*=b;
}

vec4 operator* ( vec4 a, const float b ) {
	return a*=b;
}


#endif /** VECTOR_H */
