#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif
#include "winrt/Windows.UI.ViewManagement.h"
#include "App.xaml.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Windows::Foundation;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::RSSN::implementation
{
	MainWindow::MainWindow()
	{
		InitializeComponent();
		SetTitleBar(AppTitleBar());
	}
	int32_t MainWindow::MyProperty()
	{
		throw hresult_not_implemented();
	}

	void MainWindow::MyProperty(int32_t /* value */)
	{
		throw hresult_not_implemented();
	}

	void MainWindow::ClassNameHyperlinkButton_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args)
	{

	}
	void ClassNameHyperlinkButton_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args)
	{

	}
}