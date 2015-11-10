//Cabeceras y librerias DirectX
#include <d3d11.h>

class CContextManager{
private:
	ID3D11Device *m_D3DDevice; // esta clase, el device, nos sirve para crear objetos de DirectX
	ID3D11DeviceContext *m_DeviceContext; // el contexto nos va a servir para usar objetos de DirectX
	IDXGISwapChain *m_SwapChain; // la cadena de swap
	ID3D11RenderTargetView	*m_RenderTargetView;

public:

	CContextManager();
	
	~CContextManager();

	ID3D11Device *GetDevice() const{return m_D3DDevice;}

	ID3D11DeviceContext *GetContext() const{return m_DeviceContext;}

	IDXGISwapChain *GetSwapChain() const{return m_SwapChain;}

	ID3D11RenderTargetView *GetRenderTargetView() const { return m_RenderTargetView;}


	bool Render();

	bool InitDevice(HWND hWnd, int WIDTH_APPLICATION, int HEIGHT_APPLICATION);

	bool CreateRenderTargetView();

	bool ClearRenderTargetView(float ColorRGBA[4]);

	void OMSetRenderTargets();

	void RSSetViewports();

	void Present();





};