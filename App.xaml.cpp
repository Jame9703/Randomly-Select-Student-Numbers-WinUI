#include "pch.h"
#include "App.xaml.h"
#include "MainWindow.xaml.h"
#include "winrt/Microsoft.UI.Windowing.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::RSSN::implementation
{
	winrt::Microsoft::UI::Windowing::AppWindow App::appWindow{ nullptr };
	/// <summary>
	/// Initializes the singleton application object.  This is the first line of authored code
	/// executed, and as such is the logical equivalent of main() or WinMain().
	/// </summary>
	App::App()
	{
		// Xaml objects should not call InitializeComponent during construction.
		// See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent

#if defined _DEBUG && !defined DISABLE_XAML_GENERATED_BREAK_ON_UNHANDLED_EXCEPTION
		UnhandledException([](IInspectable const&, UnhandledExceptionEventArgs const& e)
			{
				if (IsDebuggerPresent())
				{
					auto errorMessage = e.Message();
					__debugbreak();
				}
			});
#endif
	}

	/// <summary>
	/// Invoked when the application is launched.
	/// </summary>
	/// <param name="e">Details about the launch request and process.</param>
	void App::OnLaunched([[maybe_unused]] LaunchActivatedEventArgs const& e)
	{
		using namespace winrt::Microsoft::UI::Windowing;
		window = make<MainWindow>();
		appWindow = window.AppWindow();
		if (AppWindowTitleBar::IsCustomizationSupported())
		{
			//�Զ��������
			AppWindowTitleBar titleBar = appWindow.TitleBar();
			titleBar.ExtendsContentIntoTitleBar(true);
			titleBar.PreferredHeightOption(Microsoft::UI::Windowing::TitleBarHeightOption::Tall);
		}
		else
		{
			//API����֧�֣�ʹ��Ĭ�ϱ�����
			window.ExtendsContentIntoTitleBar(true);
		}
		window.Activate();
	}
}
