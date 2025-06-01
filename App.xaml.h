#pragma once

#include "App.xaml.g.h"
namespace winrt::RSSN::implementation
{
	struct App : AppT<App>
	{
		App();

		void OnLaunched(Microsoft::UI::Xaml::LaunchActivatedEventArgs const&);

	private:
		winrt::Microsoft::UI::Xaml::Window window{ nullptr };
	public:
		static winrt::Microsoft::UI::Windowing::AppWindow appWindow;
	};
}
