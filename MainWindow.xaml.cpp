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
		_lastSelectedButton = HomePageButton();//ȷ����ʼʱ_lastSelectedButton��Ϊnull
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
				// ���֮ǰ��ѡ�еİ�ť��ȡ����ѡ��״̬
				_lastSelectedButton.IsChecked(false);
				auto oldbutton_children = (_lastSelectedButton.Content().as<StackPanel>()).Children();
				for (auto&& child : oldbutton_children)
				{
					if (auto textBlock = child.try_as<TextBlock>())
					{
						textBlock.Visibility(Visibility::Visible);//��ʾ_lastSelectedButton���ı�
					}
				}
				auto newbutton_children = (button.Content().as<StackPanel>()).Children();
				for (auto&& child : newbutton_children)
				{
					if (auto textBlock = child.try_as<TextBlock>())
					{
						textBlock.Visibility(Visibility::Collapsed);//���ر��ε����ť���ı�
					}
				}
			}

			button.IsChecked(true); // ���õ�ǰ��ťΪѡ��״̬
			auto targetPosition = button.TransformToVisual(Canvas()).TransformPoint(Point(button.ActualWidth() / 2, (button.ActualHeight()) / 2));
			// ����Storyboard�Ķ���ֵ
			if (doubleAnimation() != nullptr)
			{
				doubleAnimation().To() = targetPosition.Y - MovingRectangle().Height();
			}
			MovingRectangle().Visibility(Visibility::Visible);
			rectangle().Visibility(Visibility::Collapsed);
			// ��ʼStoryboard����
			MoveRectangleStoryboard().Begin();

			_lastSelectedButton = button; // �������ѡ�еİ�ť
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
			button.IsChecked(true);//�ϴε���İ�ť�ͱ���һ��������ѡ��״̬
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
			button.IsChecked(true);//�ϴε���İ�ť�ͱ���һ��������ѡ��״̬
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
			button.IsChecked(true);//�ϴε���İ�ť�ͱ���һ��������ѡ��״̬
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
			button.IsChecked(true);//�ϴε���İ�ť�ͱ���һ��������ѡ��״̬
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
			button.IsChecked(true);//�ϴε���İ�ť�ͱ���һ��������ѡ��״̬
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
			button.IsChecked(true);//�ϴε���İ�ť�ͱ���һ��������ѡ��״̬
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
			button.IsChecked(true);//�ϴε���İ�ť�ͱ���һ��������ѡ��״̬
		}
		SettingsIcon().Glyph(L"\uF8B0");
	}
}
