/*!
	@file
	@author		Albert Semenov
	@date		01/2008
*/
/*
	This file is part of MyGUI.

	MyGUI is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	MyGUI is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with MyGUI.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef __MYGUI_TAB_CONTROL_H__
#define __MYGUI_TAB_CONTROL_H__

#include "MyGUI_Prerequest.h"
#include "MyGUI_Widget.h"
#include "MyGUI_Any.h"
#include "MyGUI_EventPair.h"
#include "MyGUI_ControllerFadeAlpha.h"
#include "MyGUI_IItem.h"
#include "MyGUI_IItemContainer.h"

namespace MyGUI
{

	typedef delegates::CMultiDelegate2<TabControl*, size_t> EventHandle_TabPtrSizeT;

	/** \brief @wpage{TabControl}
		TabControl widget description should be here.
	*/
	class MYGUI_EXPORT TabControl :
		public Widget,
		public IItemContainer,
		public MemberObsolete<TabControl>
	{
		// для уведобления об удалении
		//FIXME
		friend class TabItem;

		MYGUI_RTTI_DERIVED( TabControl )

	public:
		TabControl();

		struct TabItemInfo
		{
			TabItemInfo(int _width, int _height, const UString& _name, TabItem* _item, Any _data) :
				width(_width),
                height(_height),
				name(_name),
				item(_item),
				data(_data)
			{
			}

			int width;
            int height;
			UString name;
			TabItem* item;
			Any data;
		};

		typedef vector<TabItemInfo>::type VectorTabItemInfo;

		//! @copydoc Widget::setPosition(const IntPoint& _value)
		virtual void setPosition(const IntPoint& _value);
		//! @copydoc Widget::setSize(const IntSize& _value)
		virtual void setSize(const IntSize& _value);
		//! @copydoc Widget::setCoord(const IntCoord& _value)
		virtual void setCoord(const IntCoord& _value);

		/** @copydoc Widget::setPosition(int _left, int _top) */
		void setPosition(int _left, int _top);
		/** @copydoc Widget::setSize(int _width, int _height) */
		void setSize(int _width, int _height);
		/** @copydoc Widget::setCoord(int _left, int _top, int _width, int _height) */
		void setCoord(int _left, int _top, int _width, int _height);

		//------------------------------------------------------------------------------//
		// манипуляции айтемами

		//! Get number of items
		size_t getItemCount() const;

		//! Insert an item into a array at a specified position
		TabItem* insertItemAt(size_t _index, const UString& _name, Any _data = Any::Null);
		//! Insert an item into a array
		TabItem* insertItem(TabItem* _to, const UString& _name, Any _data = Any::Null);

		//! Add an item to the end of a array
		TabItem* addItem(const UString& _name, Any _data = Any::Null);

		//! Remove item at a specified position
		void removeItemAt(size_t _index);
		//! Remove item
		void removeItem(TabItem* _item);

		//! Remove all items
		void removeAllItems();


		//! Get item from specified position
		TabItem* getItemAt(size_t _index);

		//! Get item index
		size_t getItemIndex(TabItem* _item);

		//! Search item, returns the position of the first occurrence in array or ITEM_NONE if item not found
		size_t findItemIndex(TabItem* _item);

		//! Search item, returns the position of the first occurrence in array or ITEM_NONE if item not found
		size_t findItemIndexWith(const UString& _name);

		//! Search item, returns the item of the first occurrence in array or nullptr if item not found
		TabItem* findItemWith(const UString& _name);

		void swapItems(size_t _index1, size_t _index2);

		//------------------------------------------------------------------------------//
		// манипуляции выделениями

		//! Get index of selected item (ITEM_NONE if none selected)
		size_t getIndexSelected() const;

		//! Get selected item (nullptr if none selected)
		TabItem* getItemSelected();

		//! Select specified _index
		void setIndexSelected(size_t _index);

		//! Select item
		void setItemSelected(TabItem* _item);

        void setButtonSpace(int _space);

        void setVLayout(bool _vlayout);

        void setChangeSelect(const std::string& _name);

        void onChangeSelect(MyGUI::TabControl* _sender, size_t _index);

		//------------------------------------------------------------------------------//
		// манипуляции данными

		//! Replace an item data at a specified position
		void setItemDataAt(size_t _index, Any _data);
		//! Replace an item data
		void setItemData(TabItem* _item, Any _data);

		//! Clear an item data at a specified position
		void clearItemDataAt(size_t _index);
		//! Clear an item data
		void clearItemData(TabItem* _item);

		//! Get item data from specified position
		template <typename ValueType>
		ValueType* getItemDataAt(size_t _index, bool _throw = true)
		{
			MYGUI_ASSERT_RANGE(_index, mItemsInfo.size(), "TabControl::getItemDataAt");
			return mItemsInfo[_index].data.castType<ValueType>(_throw);
		}
		//! Get item data
		template <typename ValueType>
		ValueType* getItemData(TabItem* _item, bool _throw = true)
		{
			return getItemDataAt<ValueType>(getItemIndex(_item), _throw);
		}


		//------------------------------------------------------------------------------//
		// манипуляции отображением

		//! Replace an item name at a specified position
		void setItemNameAt(size_t _index, const UString& _name);

		//! Replace an item name
		void setItemName(TabItem* _item, const UString& _name);

		//! Get item name from specified position
		const UString& getItemNameAt(size_t _index);

		//! Get item name
		const UString& getItemName(TabItem* _item);


		//------------------------------------------------------------------------------//
		// манипуляции выдимостью

		//! Move all elements so specified becomes visible
		void beginToItemAt(size_t _index);

		//! Move all elements so specified becomes visible
		void beginToItem(TabItem* _item);
		//! Move all elements so first becomes visible
		void beginToItemFirst();
		//! Move all elements so last becomes visible
		void beginToItemLast();
		//! Move all elements so selected becomes visible
		void beginToItemSelected();


		//------------------------------------------------------------------------------//
		// остальные манипуляции

		//! Set button width at a specified position
		void setButtonWidthAt(size_t _index, int _width = DEFAULT);
		//! Set button width
		void setButtonWidth(TabItem* _item, int _width = DEFAULT);

        //! Set button width at a specified position
        void setButtonHeightAt(size_t _index, int _height = DEFAULT);
        //! Set button width
        void setButtonHeight(TabItem* _item, int _height = DEFAULT);

		//! Get button width at a specified position
		int getButtonWidthAt(size_t _index);
		//! Get button width
		int getButtonWidth(TabItem* _item);

		//------------------------------------------------------------------------------//

		/** Set default button width and disable autowidth mode */
		void setButtonDefaultWidth(int _value);
		/** Get default button width */
		int getButtonDefaultWidth() const;

        void setButtonDefaultHeight(int _value);

		/** Enable or disable button auto width */
		void setButtonAutoWidth(bool _value);
		/** Get button auto width flag */
		bool getButtonAutoWidth() const;

		/** Enable or disable smooth sheets showing */
		void setSmoothShow(bool _value);
		/** Get smooth sheets showing flag */
		bool getSmoothShow() const;

		/*events:*/
		/** Event : Active TabControl sheet changed \n
			signature : void method(MyGUI::TabControl* _sender, size_t _index)\n
			@param _sender widget that called this event
			@param _index Index of selected sheet
		*/
		EventPair<EventHandle_WidgetSizeT, EventHandle_TabPtrSizeT>
			eventTabChangeSelect;

		/*internal:*/
		// IItemContainer impl
		virtual size_t _getItemCount();
		virtual void _addItem(const MyGUI::UString& _name);
		virtual void _removeItemAt(size_t _index);
		virtual Widget* _getItemAt(size_t _index);
		virtual void _setItemNameAt(size_t _index, const UString& _name);
		virtual const UString& _getItemNameAt(size_t _index);

	protected:
		virtual void initialiseOverride();
		virtual void shutdownOverride();

		void updateBar();

		void notifyPressedButtonEvent(MyGUI::Widget* _sender);
		void notifyPressedBarButtonEvent(MyGUI::Widget* _sender);

		int _getTextWidth(const UString& _text);

		void _showItem(TabItem* _sheet, bool _show, bool _smooth);

        void _createItemButton();

        void _createItemShelter();

		void _insertItem(size_t _index, const UString& _name, TabItem* _sheet, Any _data);

		// вкладка при удалении уведомляет таб
		void _notifyDeleteItem(TabItem* _item);

		virtual void onWidgetCreated(Widget* _widget);

		virtual void setPropertyOverride(const std::string& _key, const std::string& _value);

	private:
		void actionWidgetHide(Widget* _widget, ControllerItem* _controller);

		ControllerFadeAlpha* createControllerFadeAlpha(float _alpha, float _coef, bool _enable);

		Widget* _getWidgetTemplate();
		Widget* _getWidgetBar();

        Button* createButton();
        Widget* createShelter();
		void updateBarOld();
		void updateBarNew();

	private:
		int mOffsetTab; // смещение бара при показе кнопок
		bool mButtonShow;
		int mWidthBar; // ширина в которую помещаються все кнопки
        vector<Button*>::type mItemButton; // список кнопок, не должно равно списку страниц
        vector<Widget*>::type mItemShelter; // список кнопок, не должно равно списку страниц
        std::string mButtonSkinName;
        std::string mShelterSkinName;
		std::string mEmptySkinName;

		Widget* mWidgetBar;
		Button* mButtonLeft;
		Button* mButtonRight;
		Widget* mButtonDecor;
		VectorWidgetPtr mWidgetsPatch; // список виджетов которые нужно показать при показе кнопки
		Widget* mEmptyBarWidget;
		Widget* mItemTemplate;

		// информация о вкладках
		VectorTabItemInfo mItemsInfo;
		size_t mStartIndex;
		size_t mIndexSelect;

		int mButtonDefaultWidth;
        int mButtonDefaultHeight;
		bool mSmoothShow;
		bool mButtonAutoWidth;

		// флаг, чтобы отсеч уведомления от вкладок, при общем шутдауне виджета
		bool mShutdown;

        Widget* mHeaderPlace;
        Widget* mHeaderShelter;
		Widget* mControls;
		Widget* mEmpty;

        bool mVLayout;
        int mButtonSpace;

        std::string mChangeSelect;
	};

} // namespace MyGUI

#endif // __MYGUI_TAB_CONTROL_H__
