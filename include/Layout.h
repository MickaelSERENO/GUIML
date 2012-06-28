#ifndef DEF_LAYOUT
#define DEF_LAYOUT

#include "Widget.h"

namespace guiml
{
	class Layout : public Widget
	{
	public:
		#include "SurchargeMethode.h"
		Layout(Widget *parent, const sf::FloatRect &rect, const std::vector<std::vector<Widget*> > &widgets = std::vector<std::vector<Widget*> >(), const sf::Vector2f &distance = sf::Vector2f(0, 0));
		Layout(const Layout &copy);
		Layout& operator=(const Layout &copy);
		~Layout();

		void update(std::list<sf::Drawable*> &drawable);
		void setSize(float x, float y);
		void setPosition(float x, float y);
		void setDistance(float x, float y);
		void setDistance(const sf::Vector2f &distance);
		void addWidget(const Widget *widget, const sf::Vector2f &pos, const sf::Vector2f &nbCase = sf::Vector2f(1, 1));
		void removeChild(const sf::Vector2f &pos);
		
		bool isEmpty() const;
		sf::Vector2f getSizeGrid() const;
		const Widget* getWidget(const sf::Vector2f &pos) const;
		const Widget* getWidget(unsigned int x, unsigned int y) const;
		const sf::Vector2f& getVirtualDistance() const;
		sf::Vector2f getRealDistance() const;
		virtual void resizeWidget(const sf::Vector2f& oldWindowSize, const sf::Vector2f& newWindowSize);
		sf::Vector2f hasBigWidget(const sf::Vector2f &pos) const;
		const sf::Vector2f getPosWidget(const Widget& widget) const;
	private:
		int getNumberWidgetColumn(int pos) const;
		std::vector<std::vector<Widget*> > m_widgetList;
		std::vector<std::vector<sf::Vector2f> > m_sizeWidget;
		sf::Vector2f m_distance;
		sf::Vector2f m_scale;
	};
}

#endif
