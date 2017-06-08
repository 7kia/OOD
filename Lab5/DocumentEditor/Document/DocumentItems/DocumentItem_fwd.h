#pragma once

#include <memory>

class CDocumentItem;
class CConstDocumentItem;
class IParagraph;
class IImage;

using DocumentItemPtr = std::shared_ptr<CDocumentItem>;

using IParagraphPtr = std::shared_ptr<IParagraph>;
using IImagePtr = std::shared_ptr<IImage>;
using IParagraphConstPtr = std::shared_ptr<const IParagraph>;
using IImageConstPtr = std::shared_ptr<const IImage>;
