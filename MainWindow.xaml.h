#pragma once

#include "MainWindow.g.h"
using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Controls::Primitives;
using namespace Windows::Foundation;

namespace winrt::RSSN::implementation
{
	struct MainWindow : MainWindowT<MainWindow>
	{
		MainWindow();
		// Xaml objects should not call InitializeComponent during construction.
		// See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
		int32_t MyProperty();
		void MyProperty(int32_t value);
		ToggleButton  _lastSelectedButton;
		void HomePageButton_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void ClassPageButton_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void NumbersPageButton_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void CharactersPageButton_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void HelpPageButton_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void MorePageButton_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void SettingsPageButton_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void StartAnimation(ToggleButton const& button);
	};
}

namespace winrt::RSSN::factory_implementation
{
	struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
	{
	};
}
