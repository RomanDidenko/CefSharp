﻿// Copyright © 2010-2015 The CefSharp Authors. All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be found in the LICENSE file.

#pragma once

#include "Stdafx.h"

#include "Internals/TypeConversion.h"

using namespace System;
using namespace System::Collections::Specialized;
using namespace CefSharp;

namespace CefSharp
{
    namespace Internals
    {
        public ref class CefPostDataElementWrapper : public IPostDataElement
        {
            MCefRefPtr<CefPostDataElement> _postDataElement;
        internal:
            CefPostDataElementWrapper(CefRefPtr<CefPostDataElement> postDataElement) :
                _postDataElement(postDataElement)
            {
                
            }

            !CefPostDataElementWrapper()
            {
                _postDataElement = nullptr;
            }

            ~CefPostDataElementWrapper()
            {
                this->!CefPostDataElementWrapper();
            }

        public:
            virtual property bool IsReadOnly
            {
                bool get()
                {
                    return _postDataElement->IsReadOnly();
                }
            }

            virtual property String^ File
            {
                String^ get()
                {
                    return StringUtils::ToClr(_postDataElement->GetFile());
                }
                void set(String^ val)
                {
                    _postDataElement->SetToFile(StringUtils::ToNative(val));
                }
            }

            virtual void SetToEmpty()
            {
                _postDataElement->SetToEmpty();
            }

            virtual property PostDataElementType Type
            {
                PostDataElementType get()
                {
                    return (PostDataElementType)_postDataElement->GetType();
                }
            }

            virtual property array<Byte>^ Bytes
            {
                array<Byte>^ get()
                {
                    auto byteCount = _postDataElement->GetBytesCount();
                    if (byteCount == 0)
                    {
                        return nullptr;
                    }

                    auto bytes = gcnew array<Byte>(byteCount);
                    pin_ptr<Byte> src = &bytes[0]; // pin pointer to first element in arr

                    _postDataElement->GetBytes(byteCount, static_cast<void*>(src));

                    return bytes;
                }
                void set(array<Byte>^ val)
                {
                    pin_ptr<Byte> src = &val[0];
                    _postDataElement->SetToBytes(val->Length, static_cast<void*>(src));
                }
            }
        };
    }
}
