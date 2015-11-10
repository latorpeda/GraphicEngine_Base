#include "ContextManager.h"


CContextManager::CContextManager(){
	this->m_D3DDevice = NULL;
	this->m_DeviceContext = NULL; // el contexto nos va a servir para usar objetos de DirectX
	this->m_SwapChain = NULL; // la cadena de swap	
	this->m_RenderTargetView = NULL;
}

CContextManager::~CContextManager(){
	this->m_D3DDevice->Release();
	this->m_DeviceContext->Release();
	this->m_SwapChain->Release();
	this->m_RenderTargetView->Release();
}
	

bool CContextManager::Render(){
	float color[4] ={0,0,1,1};
	this->ClearRenderTargetView(color);
	this->m_DeviceContext->OMSetRenderTargets(1,&m_RenderTargetView, nullptr);
	D3D11_VIEWPORT pviewport ={0,0,800,600,0,1};
	this->m_DeviceContext->RSSetViewports(1,&pviewport);
	this->m_SwapChain->Present(0,0);
	return true;
}

bool CContextManager::InitDevice(HWND hWnd, int WIDTH_APPLICATION, int HEIGHT_APPLICATION){
	// Tendremos que crear y rellenar una estructura de este tipo
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	// o
	//DXGI_SWAP_CHAIN_DESC desc = {};
	desc.BufferCount = 1;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.Windowed = TRUE;
	// TODO:
	desc.BufferDesc.Width = WIDTH_APPLICATION;
	desc.BufferDesc.Height = HEIGHT_APPLICATION;
	desc.BufferDesc.RefreshRate.Numerator = 1;
	desc.BufferDesc.RefreshRate.Denominator = 60;
	desc.OutputWindow = hWnd;
	desc.SampleDesc.Count = 1;
	//desc.SampleDesc.Quality;
	//desc. ????

	// Que DirectX queremos
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);
		

	//Rellenamos contextManager
	if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, featureLevels, numFeatureLevels, D3D11_SDK_VERSION, &desc, &this->m_SwapChain,  &this->m_D3DDevice, NULL, &this->m_DeviceContext)))
	{
		return S_FALSE;
	}
	return S_OK;
}

bool CContextManager::CreateRenderTargetView(){
	ID3D11Texture2D *pBackBuffer;
	if (FAILED(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer)))
		return FALSE;
	HRESULT hr = m_D3DDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_RenderTargetView);
	pBackBuffer->Release();
	return TRUE;
}

// Limpiar el framebuffer:
bool CContextManager::ClearRenderTargetView(float ColorRGBA[4]){	
	this->m_DeviceContext->ClearRenderTargetView(this->m_RenderTargetView,ColorRGBA);
	return true;	
}


	
