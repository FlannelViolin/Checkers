//Pack matrices so that they're all row major like GLSL
#pragma pack_matrix(row_major)

cbuffer perModel : register(b0)
{
	matrix worldMatrix;
	matrix modelMatrix;
	matrix rotationMatrix;

	texture2D tex;

	float3 lookAt;
	float3 eyePoint;
};

struct VertexShaderInput
{
	float3 position		: POSITION;
	float3 normal		: NORMAL;
	float2 texCoord		: TEXCOORD;
};

struct VertexToPixel
{
	float4 position		: SV_POSITION;
	float2 texCoord		: TEX_COORD0;

	float3 worldNormal	: TEX_COORD1;
	float3 worldPosition: TEX_COORD2;
	float3 eyePosition	: TEX_COORD3;

	float2 glowCoords[8]	: TEX_COORD4;
	/*float2 texCoordtm	: TEX_COORD5;
	float2 texCoordtr	: TEX_COORD6;
	float2 texCoordml	: TEX_COORD7;
	float2 texCoordmr	: TEX_COORD8;
	float2 texCoordbr	: TEX_COORD9;
	float2 texCoordbm	: TEX_COORD10;
	float2 texCoordbl	: TEX_COORD11;*/
};

VertexToPixel main(VertexShaderInput input)
{
	VertexToPixel output;
	float2 mother = input.texCoord;

	// Calculate output position
	output.position = mul(float4(input.position, 1.0f), worldMatrix);
	output.texCoord = mother;

	//calculate sample targets
	output.glowCoords[0][0] = mother[0] - 1; output.glowCoords[0][1] = mother[1] - 1;
	output.glowCoords[1][0] = mother[0];	 output.glowCoords[1][1] = mother[1] - 1;
	output.glowCoords[2][0] = mother[0] + 1; output.glowCoords[2][1] = mother[1] - 1;
	
	output.glowCoords[3][0] = mother[0] - 1; output.glowCoords[3][1] = mother[1];
	output.glowCoords[4][0] = mother[0] + 1; output.glowCoords[4][1] = mother[1];

	output.glowCoords[5][0] = mother[0] - 1; output.glowCoords[5][1] = mother[1] + 1;
	output.glowCoords[6][0] = mother[0];	 output.glowCoords[6][1] = mother[1] + 1;
	output.glowCoords[7][0] = mother[0] + 1; output.glowCoords[7][1] = mother[1] + 1;

	//try to do some lighting
	float4 worldCoord4v = mul(float4(input.position, 1.0f),modelMatrix);
	float3 worldCoord3v = float3(worldCoord4v.x / worldCoord4v.w,
								 worldCoord4v.y / worldCoord4v.w,
								 worldCoord4v.z / worldCoord4v.w);

	float3x3 rotation = (float3x3)rotationMatrix;
	float3 worldNormal3v = mul(input.normal, rotation);

	//test glow

	//

	output.worldNormal = worldNormal3v;
	output.worldPosition = worldCoord3v;
	output.eyePosition = eyePoint;

	return output;
}