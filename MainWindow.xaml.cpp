#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif
#include "winrt/Windows.UI.ViewManagement.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Windows::Foundation;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::RSSN::implementation
{
    MainWindow::MainWindow()
    {
        this->ExtendsContentIntoTitleBar(true);
        this->SetTitleBar(AppTitleBar());
        //auto titleBar = winrt::Windows::UI::ViewManagement::ApplicationView::GetForCurrentView().TitleBar();
        //titleBar.ExtendViewIntoTitleBar(true);
        //titleBar.ButtonBackgroundColor(winrt::Windows::UI::Colors::Transparent()); // ���ð�ť����͸��
        //titleBar.ButtonForegroundColor(winrt::Windows::UI::Colors::White()); // ���ð�ťǰ��ɫΪ��ɫ
        //titleBar.BackgroundColor(winrt::Windows::UI::Colors::Black()); // ���ñ���������ɫΪ��ɫ
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
