#ifndef DEF_LAYOUT
#define DEF_LAYOUT

#include "Widget.h"

namespace guiml
{
	class Layout : public Widget
	{
	public:
		#include "SurchargeMethode.h"
		Layout(Widget *parent, const sf::IntRect &rect, const std::vector<std::vector<Widget*> > &widgets = std::vector<std::vector<Widget*> >(), const sf::Vector2i &distance = sf::Vector2i(0, 0));
		Layout(const Layout &copy);
		Layout& operator=(const Layout &copy);
		~Layout();

		void update(std::list<sf::Drawable*> &drawable);
		void setSize(int x, int y);
		void setPosition(int x, int y);
		void setDistance(unsigned int x, unsigned int y);
		void setDistance(const sf::Vector2i &distance);
		void addWidget(const Widget *widget, const sf::Vector2i &pos, const sf::Vector2i &nbCase = sf::Vector2i(1, 1));
		void removeChild(const sf::Vector2i &pos);
		
		bool isEmpty() const;
		sf::Vector2i getSizeGrid() const;
		const Widget* getWidget(const sf::Vector2i &pos) const;
		const Widget* getWidget(unsigned int x, unsigned int y) const;
		const sf::Vector2i& getVirtualDistance() const;
		sf::Vector2i getRealDistance() const;
		virtual void resizeWidget(const sf::Vector2i& oldWindowSize, const sf::Vector2i& newWindowSize);
		sf::Vector2i hasBigWidget(const sf::Vector2i &pos) const;
		const sf::Vector2i getPosWidget(const Widget& widget) const;
	private:
		int getNumberWidgetColumn(int pos) const;
		std::vector<std::vector<Widget*> > m_widgetList;
		std::vector<std::vector<sf::Vector2i> > m_sizeWidget;
		sf::Vector2i m_distance;
		sf::Vector2f m_scale;
	};
}

#endif
