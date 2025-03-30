#include "pch.h"
#include "RippleHelper.h"
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.UI.h>
#include <winrt/Windows.UI.Composition.h>
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Hosting.h>
#include <winrt/Windows.UI.Xaml.Input.h>
#include <winrt/Windows.UI.Xaml.Media.h>
using namespace winrt::Windows::UI::Xaml;
using namespace winrt::Windows::UI::Xaml::Controls;
using namespace winrt::Windows::UI::Xaml::Hosting;
using namespace winrt::Windows::UI::Xaml::Input;
using namespace winrt::Windows::UI::Composition;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;

namespace 随机抽取学号::Classes
{
    // 定义RippleHelperState枚举，对应C#中的同名枚举
    enum class RippleHelperState
    {
        None,
        Pressed,
        Released
    };

    // RippleHelper类，对应C#中的同名类，继承自DependencyObject
    class RippleHelper : public DependencyObject
    {
    public:
        // 模拟C#中的静态字段声明
        static winrt::Windows::UI::Xaml::RoutedEventHandler pointerEventHandler;

        // 模拟C#中的静态属性获取方式，这里以SizeBind为例，其他类似
        static ExpressionAnimation SizeBind()
        {
            static ExpressionAnimation sizeBind;
            if (!sizeBind)
            {
                Compositor compositor = Window::Current().Compositor();
                sizeBind = compositor.CreateExpressionAnimation(L"hostVisual.Size");
            }
            return sizeBind;
        }

        static CompositionEasingFunction EaseOut()
        {
            static CompositionEasingFunction easeOut;
            if (!easeOut)
            {
                Compositor compositor = Window::Current().Compositor();
                easeOut = compositor.CreateCubicBezierEasingFunction(Vector2{ 0.0f, 0.0f }, Vector2{ 0.9f, 1.0f });
            }
            return easeOut;
        }

        static ScalarKeyFrameAnimation OpacityAnimation()
        {
            static ScalarKeyFrameAnimation opacityAnimation;
            if (!opacityAnimation)
            {
                Compositor compositor = Window::Current().Compositor();
                opacityAnimation = compositor.CreateScalarKeyFrameAnimation();
                opacityAnimation.InsertKeyFrame(0.0f, 1.0f, EaseOut());
                opacityAnimation.InsertKeyFrame(1.0f, 0.0f, EaseOut());
                opacityAnimation.Duration(TimeSpan{ 0, 0, 0, 0, 350 });
                opacityAnimation.Target(L"Opacity");
            }
            return opacityAnimation;
        }

        static Vector3KeyFrameAnimation ScaleAnimation()
        {
            static Vector3KeyFrameAnimation scaleAnimation;
            if (!scaleAnimation)
            {
                Compositor compositor = Window::Current().Compositor();
                scaleAnimation = compositor.CreateVector3KeyFrameAnimation();
                scaleAnimation.InsertKeyFrame(0.0f, float3{ 0.0f, 0.0f, 1.0f }, EaseOut());
                scaleAnimation.InsertExpressionKeyFrame(0.8f, L"Vector3(propSet.ScaleValue,propSet.ScaleValue,1f)", EaseOut());
                scaleAnimation.InsertExpressionKeyFrame(1.0f, L"Vector3(propSet.ScaleValue,propSet.ScaleValue,1f)", EaseOut());
                scaleAnimation.SetReferenceParameter(L"propSet", PropSet());
                scaleAnimation.Duration(TimeSpan{ 0, 0, 0, 0, 320 });
                scaleAnimation.Target(L"Scale");
            }
            return scaleAnimation;
        }

        static CompositionAnimationGroup RippleAnimationGroup()
        {
            static CompositionAnimationGroup rippleAnimationGroup;
            if (!rippleAnimationGroup)
            {
                rippleAnimationGroup = Window::Current().Compositor().CreateAnimationGroup();
                rippleAnimationGroup.Children().Append(OpacityAnimation());
                rippleAnimationGroup.Children().Append(ScaleAnimation());
            }
            return rippleAnimationGroup;
        }

        static CompositionPropertySet PropSet()
        {
            static CompositionPropertySet propSet;
            if (!propSet)
            {
                Compositor compositor = Window::Current().Compositor();
                propSet = compositor.CreatePropertySet();
                propSet.InsertScalar(L"ScaleValue", 2.0f);
            }
            return propSet;
        }

        static CompositionBrush Mask()
        {
            static CompositionBrush mask;
            if (!mask)
            {
                Uri uri{ L"ms-appx:///Assets/Photos/RippleMask.png" };
                Windows::Foundation::Size size{ 100.0, 100.0 };
                auto surface = LoadedImageSurface::StartLoadFromUri(uri, size);
                Compositor compositor = Window::Current().Compositor();
                mask = compositor.CreateSurfaceBrush(surface);
            }
            return mask;
        }

        // 模拟C#中的附加属性的获取和设置方法，以下以IsFillEnable为例，其他类似
        static bool GetIsFillEnable(DependencyObject obj)
        {
            return winrt::unbox_value<bool>(obj.GetValue(IsFillEnableProperty()));
        }

        static void SetIsFillEnable(DependencyObject obj, bool value)
        {
            obj.SetValue(IsFillEnableProperty(), winrt::box_value(value));
        }

        static DependencyProperty IsFillEnableProperty()
        {
            static DependencyProperty property = DependencyProperty::RegisterAttached(
                L"IsFillEnable",
                winrt::xaml_typename<bool>(),
                winrt::xaml_typename<RippleHelper>(),
                PropertyMetadata(true));
            return property;
        }

        static TimeSpan GetRippleDuration(UIElement obj)
        {
            return winrt::unbox_value<TimeSpan>(obj.GetValue(RippleDurationProperty()));
        }

        static void SetRippleDuration(UIElement obj, TimeSpan value)
        {
            obj.SetValue(RippleDurationProperty(), winrt::box_value(value));
        }

        static DependencyProperty RippleDurationProperty()
        {
            static DependencyProperty property = DependencyProperty::RegisterAttached(
                L"RippleDuration",
                winrt::xaml_typename<TimeSpan>(),
                winrt::xaml_typename<RippleHelper>(),
                PropertyMetadata(TimeSpan{ 0, 0, 0, 0, 330 }));
            return property;
        }

        static double GetRippleRadius(UIElement obj)
        {
            return winrt::unbox_value<double>(obj.GetValue(RippleRadiusProperty()));
        }

        static void SetRippleRadius(UIElement obj, double value)
        {
            obj.SetValue(RippleRadiusProperty(), winrt::box_value(value));
        }

        static DependencyProperty RippleRadiusProperty()
        {
            static DependencyProperty property = DependencyProperty::RegisterAttached(
                L"RippleRadius",
                winrt::xaml_typename<double>(),
                winrt::xaml_typename<RippleHelper>(),
                PropertyMetadata(100.0));
            return property;
        }

        static Windows::UI::Color GetRippleColor(UIElement obj)
        {
            return winrt::unbox_value<Windows::UI::Color>(obj.GetValue(RippleColorProperty()));
        }

        static void SetRippleColor(UIElement obj, Windows::UI::Color value)
        {
            obj.SetValue(RippleColorProperty(), winrt::box_value(value));
        }

        static DependencyProperty RippleColorProperty()
        {
            static DependencyProperty property = DependencyProperty::RegisterAttached(
                L"RippleColor",
                winrt::xaml_typename<Windows::UI::Color>(),
                winrt::xaml_typename<RippleHelper>(),
                PropertyMetadata(Windows::UI::Colors::White));
            return property;
        }

        static RippleHelperState GetRippleHelperState(UIElement obj)
        {
            return winrt::unbox_value<RippleHelperState>(obj.GetValue(RippleHelperStateProperty()));
        }

        static void SetRippleHelperState(UIElement obj, RippleHelperState value)
        {
            obj.SetValue(RippleHelperStateProperty(), winrt::box_value(value));
        }

        static DependencyProperty RippleHelperStateProperty()
        {
            static DependencyProperty property = DependencyProperty::RegisterAttached(
                L"RippleHelperState",
                winrt::xaml_typename<RippleHelperState>(),
                winrt::xaml_typename<RippleHelper>(),
                PropertyMetadata(
                    RippleHelperState::None,
                    [](DependencyObject const& sender, PropertyChangedEventArgs const& args)
                    {
                        if (args.NewValue() && args.NewValue() != args.OldValue())
                        {
                            RippleHelperState value = winrt::unbox_value<RippleHelperState>(args.NewValue());
                            RippleHelperState oldvalue = winrt::unbox_value<RippleHelperState>(args.OldValue());
                            if (sender.try_as<UIElement>())
                            {
                                UIElement ele = sender.as<UIElement>();
                                switch (value)
                                {
                                case RippleHelperState::Pressed:
                                {
                                    ele.RemoveHandler(UIElement::PointerReleasedEvent(), pointerEventHandler);
                                    ele.AddHandler(UIElement::PointerPressedEvent(), pointerEventHandler, true);
                                }
                                break;
                                case RippleHelperState::Released:
                                {
                                    ele.RemoveHandler(UIElement::PointerPressedEvent(), pointerEventHandler);
                                    ele.AddHandler(UIElement::PointerReleasedEvent(), pointerEventHandler, true);
                                }
                                break;
                                case RippleHelperState::None:
                                {
                                    ele.RemoveHandler(UIElement::PointerPressedEvent(), pointerEventHandler);
                                    ele.RemoveHandler(UIElement::PointerReleasedEvent(), pointerEventHandler);
                                    ElementCompositionPreview::SetElementChildVisual(ele, nullptr);
                                }
                                break;
                                }
                            }
                        }
                    }
                ));
            return property;
        }

        // 模拟C#中的事件声明及触发机制
        static winrt::event_token RippleComplated(winrt::Windows::UI::Xaml::EventHandler<UIElement, Windows::Foundation::IInspectable> const& handler)
        {
            return m_rippleComplated.add(handler);
        }

        static void RippleComplated(winrt::event_token const& token)
        {
            m_rippleComplated.remove(token);
        }

        static void StartRippleAnimation(UIElement ele, Vector2 position)
        {
            StartRippleAnimation(ele, position, GetRippleColor(ele), GetIsFillEnable(ele), GetRippleDuration(ele), GetRippleRadius(ele));
        }

        static void StartRippleAnimation(UIElement ele, Vector2 position, Windows::UI::Color color, bool isFillEnable, TimeSpan duration, double radius = 0.0)
        {
            Visual hostVisual = ElementCompositionPreview::GetElementVisual(ele);
            Compositor compositor = Window::Current().Compositor();
            ContainerVisual cVisual = ele ? ElementCompositionPreview::GetElementChildVisual(ele).try_as<ContainerVisual>() : nullptr;
            if (!cVisual)
            {
                cVisual = compositor.CreateContainerVisual();
                SizeBind().ClearParameter(L"hostVisual");
                SizeBind().SetReferenceParameter(L"hostVisual", hostVisual);
                cVisual.StartAnimation(L"Size", SizeBind());
                Control control = ele.try_as<Control>();
                if (control)
                {
                    RoundedRectangleGeometry geometry = compositor.CreateRoundedRectangleGeometry();
                    geometry.Size(Vector2{ (float)ele.RenderSize().Width, (float)ele.RenderSize().Height });
                    geometry.CornerRadius(Vector2{ (float)control.CornerRadius().TopLeft, (float)control.CornerRadius().TopRight });
                    cVisual.Clip(compositor.CreateGeometricClip(geometry));
                }
                ElementCompositionPreview::SetElementChildVisual(ele, cVisual);
            }

            SpriteVisual sVisual = CreateSpriteVisual(ele, color);
            cVisual.Children().InsertAtTop(sVisual);
            sVisual.Offset(Vector3{ position.X, position.Y, 0.0f });

            if (isFillEnable)
            {
                double nWidth = std::max(std::max(position.X, ele.RenderSize().Width - position.X), std::max(position.Y, ele.RenderSize().Height - position.Y));
                double r = std::sqrt(nWidth * nWidth * 2);
                float finalScale = (float)r / 45.0f;
                PropSet().InsertScalar(L"ScaleValue", finalScale);
                ScaleAnimation().Duration(TimeSpan{ 0, 0, 0, 0, 400 });
                OpacityAnimation().Duration(TimeSpan{ 0, 0, 0, 0, 430 });
            }
            else
            {
                if (radius == 100.0)
                {
                    PropSet().InsertScalar(L"ScaleValue", 2.0f);
                }
                else
                {
                    PropSet().InsertScalar(L"ScaleValue", (float)GetRippleRadius(ele) / 45.0f);
                }
            }

            ScaleAnimation().Duration(duration);
            OpacityAnimation().Duration(duration);

            CompositionCommitBatch batch = compositor.GetCommitBatch(CompositionBatchTypes::Animation);
            batch.Completed([ele](const winrt::Windows::Foundation::IInspectable& sender, const winrt::Windows::UI::Composition::CompositionBatchCompletedEventArgs& args)
                {
                    RippleComplated(*this, ele, nullptr);
                    cVisual.Children().Remove(sVisual);
                });
            sVisual.StartAnimationGroup(RippleAnimationGroup());
        }

    private:
        static SpriteVisual CreateSpriteVisual(UIElement ele, Windows::UI::Color color)
        {
            Compositor compositor = Window::Current().Compositor();
            SpriteVisual sVisual = compositor.CreateSpriteVisual();
            sVisual.AnchorPoint(Vector2{ 0.5f, 0.5f });
            sVisual.Size(Vector2{ 100.0f, 100.0f });
            MaskBrush maskBrush = compositor.CreateMaskBrush();
            maskBrush.Mask(Mask());
            maskBrush.Source(compositor.CreateColorBrush(color));
            sVisual.Brush(maskBrush);
            sVisual.Size(Vector2{ 100.0f, 100.0f });
            return sVisual;
        }

        static void Ele_PointerPressed(const winrt::Windows::Foundation::IInspectable& sender, const winrt::Windows::UI::Xaml::RoutedEventArgs& e)
        {
            if (sender.try_as<UIElement>())
            {
                UIElement ele = sender.as<UIElement>();
                Vector2 position = e.GetCurrentPoint(ele).Position().ToVector2();
                StartRippleAnimation(ele, position);
            }
        }

        static void Ele_PointerReleased(const winrt::Windows::Foundation::IInspectable& sender, const winrt::Windows::UI::Xaml::RoutedEventArgs& e)
        {
            if (sender.try_as<UIElement>())
            {
                UIElement ele = sender.as<UIElement>();
                Vector2 position = e.GetCurrentPoint(ele).Position().ToVector2();
                StartRippleAnimation(ele, position);
            }
        }

        // 用于存储事件处理程序列表，模拟C#中的事件机制
        static winrt::Windows::UI::Xaml::EventHandler<UIElement, Windows::Foundation::IInspectable> m_rippleComplated;
    };

    // 初始化静态成员变量
    winrt::Windows::UI::Xaml::RoutedEventHandler RippleHelper::pointerEventHandler = RippleHelper::Ele_PointerReleased;
    winrt::Windows::UI::Xaml::EventHandler<UIElement, Windows::Foundation::IInspectable> RippleHelper::m_rippleComplated;
}