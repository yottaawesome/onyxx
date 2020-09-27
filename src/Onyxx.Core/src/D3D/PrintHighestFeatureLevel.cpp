#include "pch.hpp"
#include "include/D3D/D3D.hpp"

namespace Onyxx::Core::D3D
{
	bool PrintHighestFeatureLevel()
	{
		// Step 1: acquire device
		Microsoft::WRL::ComPtr<ID3D12Device> d3d12Device;
		HRESULT hr = D3D12CreateDevice(
			nullptr, // use default adapter
			D3D_FEATURE_LEVEL_12_1, // https://docs.microsoft.com/en-us/windows/desktop/api/d3dcommon/ne-d3dcommon-d3d_feature_level
			IID_PPV_ARGS(&d3d12Device)
		);

		if (FAILED(hr))
		{
			std::wcout << L"D3D12CreateDevice() failed" << std::endl;
			return false;
		}

		// Step 2: arrange feature levels and presentation
		const int numFeatureLevels = 5;
		D3D_FEATURE_LEVEL featureLevels[numFeatureLevels] =
		{
			D3D_FEATURE_LEVEL_12_1,	// Check for 12.1 support
			D3D_FEATURE_LEVEL_12_0,	// Then check for 12 support
			D3D_FEATURE_LEVEL_11_0, // Then check for API 11 support
			D3D_FEATURE_LEVEL_10_0,	// And so on...
			D3D_FEATURE_LEVEL_9_3
		};

		std::map<D3D_FEATURE_LEVEL, std::wstring> featureLevel =
		{
			{ D3D_FEATURE_LEVEL_12_1,	L"D3D12.1" },
			{ D3D_FEATURE_LEVEL_12_0,	L"D3D12.0" },
			{ D3D_FEATURE_LEVEL_11_0,	L"D3D11.0" },
			{ D3D_FEATURE_LEVEL_10_0,	L"D3D10.0" },
			{ D3D_FEATURE_LEVEL_9_3,	L"D3D9.3" }
		};

		// Step 3: populate request struct
		D3D12_FEATURE_DATA_FEATURE_LEVELS featureLevelsInfo;
		featureLevelsInfo.NumFeatureLevels = numFeatureLevels;
		featureLevelsInfo.pFeatureLevelsRequested = featureLevels;

		// Step 4: request information 
		hr = d3d12Device->CheckFeatureSupport(
			D3D12_FEATURE_FEATURE_LEVELS, 
			&featureLevelsInfo, 
			sizeof(featureLevelsInfo)
		);
		if (FAILED(hr))
		{
			std::wcout << L"CheckFeatureSupport() failed" << std::endl;
			return false;
		}

		std::cout << "Checking support for the following feature levels: " << std::endl;
		for (auto const& key : featureLevels)
			std::wcout << "    " << featureLevel[key] << std::endl;

		// Step 5: print information
		std::wcout
			<< std::endl
			<< "Highest feature level supported: "
			<< featureLevel[featureLevelsInfo.MaxSupportedFeatureLevel]
			<< std::endl;

		return true;
	}
}