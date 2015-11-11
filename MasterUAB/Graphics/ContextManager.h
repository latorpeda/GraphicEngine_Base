//Cabeceras y librerias DirectX
#include <d3d11.h>
//#include <Math\MathUtils.h>
#include <assert.h>
#include <Math\Matrix44.h>

class CContextManager{
private:
	ID3D11Device *m_D3DDevice; // esta clase, el device, nos sirve para crear objetos de DirectX
	ID3D11DeviceContext *m_DeviceContext; // el contexto nos va a servir para usar objetos de DirectX
	IDXGISwapChain *m_SwapChain; // la cadena de swap
	ID3D11RenderTargetView	*m_RenderTargetView; //Para pintar texturas&RenderText...

	struct EffectStruct
	{
		ID3D11VertexShader* m_VertexShader;
		ID3D11PixelShader* m_PixelShader;
		ID3D11InputLayout* m_VertexLayout;
		ID3D11Buffer* m_ConstantBuffer;
		ID3D11Buffer* m_VertexBuffer;
	};

	struct CEffectParameters
	{
		public:
			Mat44f				m_World;
			Mat44f				m_View;
			Mat44f				m_Projection;
			float				m_BaseColor[4]; //Antes CColor
			Vect4f				m_CameraRightVector;
			Vect4f				m_CameraUpVector;
			float				m_DebugRenderScale;

			uint8				offset[9]; //antes uint8_t
	};

public:

	CContextManager();	
	~CContextManager();

	ID3D11Device *GetDevice() const{return m_D3DDevice;}
	ID3D11DeviceContext *GetContext() const{return m_DeviceContext;}
	IDXGISwapChain *GetSwapChain() const{return m_SwapChain;}
	ID3D11RenderTargetView *GetRenderTargetView() const { return m_RenderTargetView;}

	bool InitDevice(HWND hWnd, int WIDTH_APPLICATION, int HEIGHT_APPLICATION);

	bool CreateRenderTargetView();

	void CreateDataForTriangle();

	void ClearRenderTargetView(float ColorRGBA[4]);

	void Render();

	void CContextManager::OnBeginDraw();

	void CContextManager::OnEndDraw();

	void Present();

	//SHADER.CPP
	EffectStruct LoadDebugEffect();

	
};