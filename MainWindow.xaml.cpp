#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif
#include "winrt/Windows.UI.ViewManagement.h"
#include "App.xaml.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Controls::Primitives;
using namespace Windows::Foundation;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::RSSN::implementation
{
	MainWindow::MainWindow()
	{
		InitializeComponent();
		SetTitleBar(AppTitleBar());
		HomePageButton().IsChecked(true);
		_lastSelectedButton = HomePageButton();//确保开始时_lastSelectedButton不为null
	}
	int32_t MainWindow::MyProperty()
	{
		throw hresult_not_implemented();
	}

	void MainWindow::MyProperty(int32_t /* value */)
	{
		throw hresult_not_implemented();
	}
	void MainWindow::StartAnimation(ToggleButton const& button)
	{
		if (button != nullptr)
		{
			if (_lastSelectedButton != nullptr)
			{
				// 如果之前有选中的按钮，取消其选中状态
				_lastSelectedButton.IsChecked(false);
				auto oldbutton_children = (_lastSelectedButton.Content().as<StackPanel>()).Children();
				for (auto&& child : oldbutton_children)
				{
					if (auto textBlock = child.try_as<TextBlock>())
					{
						textBlock.Visibility(Visibility::Visible);//显示_lastSelectedButton的文本
					}
				}
				auto newbutton_children = (button.Content().as<StackPanel>()).Children();
				for (auto&& child : newbutton_children)
				{
					if (auto textBlock = child.try_as<TextBlock>())
					{
						textBlock.Visibility(Visibility::Collapsed);//隐藏本次点击按钮的文本
					}
				}
			}

			button.IsChecked(true); // 设置当前按钮为选中状态
			auto targetPosition = button.TransformToVisual(Canvas()).TransformPoint(Point(button.ActualWidth() / 2, (button.ActualHeight()) / 2));
			// 设置Storyboard的动画值
			if (doubleAnimation() != nullptr)
			{
				doubleAnimation().To() = targetPosition.Y - MovingRectangle().Height();
			}
			MovingRectangle().Visibility(Visibility::Visible);
			rectangle().Visibility(Visibility::Collapsed);
			// 开始Storyboard动画
			MoveRectangleStoryboard().Begin();

			_lastSelectedButton = button; // 更新最后选中的按钮
			HomeIcon().Glyph(L"\uE80F");
			ClassIcon().Glyph(L"\uE77B");
			NumbersIcon().Visibility(Visibility::Visible);
			NumbersIconChecked().Visibility(Visibility::Collapsed);
			SettingsIcon().Glyph(L"\uE713");
		}
	}

	void MainWindow::HomePageButton_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		auto button = sender.as<ToggleButton>();
		if (_lastSelectedButton != button)
		{
			StartAnimation(button);
			//ContentFrame().Navigate(xaml_typename<HomePage>());
		}
		else
		{
			button.IsChecked(true);//上次点击的按钮和本次一样，保持选中状态
		}
		HomeIcon().Glyph(L"\uEA8A");
	}

	void MainWindow::ClassPageButton_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		auto button = sender.as<ToggleButton>();
		if (_lastSelectedButton != button)
		{
			StartAnimation(button);
			//ContentFrame().Navigate(xaml_typename<ClassPage>());
		}
		else
		{
			button.IsChecked(true);//上次点击的按钮和本次一样，保持选中状态
		}
		ClassIcon().Glyph(L"\uEA8C");
	}

	void MainWindow::NumbersPageButton_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		auto button = sender.as<ToggleButton>();
		if (_lastSelectedButton != button)
		{
			StartAnimation(button);
			//ContentFrame().Navigate(xaml_typename<NumbersPage>());
		}
		else
		{
			button.IsChecked(true);//上次点击的按钮和本次一样，保持选中状态
		}
		NumbersIcon().Visibility(Visibility::Collapsed);
		NumbersIconChecked().Visibility(Visibility::Visible);
	}

	void MainWindow::CharactersPageButton_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		auto button = sender.as<ToggleButton>();
		if (_lastSelectedButton != button)
		{
			StartAnimation(button);
			//ContentFrame().Navigate(xaml_typename<CharactersPage>());
		}
		else
		{
			button.IsChecked(true);//上次点击的按钮和本次一样，保持选中状态
		}
	}

	void MainWindow::HelpPageButton_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		auto button = sender.as<ToggleButton>();
		if (_lastSelectedButton != button)
		{
			StartAnimation(button);
			//ContentFrame().Navigate(xaml_typename<HelpPage>());
		}
		else
		{
			button.IsChecked(true);//上次点击的按钮和本次一样，保持选中状态
		}
	}

	void MainWindow::MorePageButton_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		auto button = sender.as<ToggleButton>();
		if (_lastSelectedButton != button)
		{
			StartAnimation(button);
			//ContentFrame().Navigate(xaml_typename<MorePage>());
		}
		else
		{
			button.IsChecked(true);//上次点击的按钮和本次一样，保持选中状态
		}
	}

	void MainWindow::SettingsPageButton_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		auto button = sender.as<ToggleButton>();
		if (_lastSelectedButton != button)
		{
			StartAnimation(button);
			//ContentFrame().Navigate(xaml_typename<SettingsPage>());
		}
		else
		{
			button.IsChecked(true);//上次点击的按钮和本次一样，保持选中状态
		}
		SettingsIcon().Glyph(L"\uF8B0");
	}
}
