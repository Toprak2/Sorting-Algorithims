#include<SFML/Graphics.hpp> 
#include "Button.h"
#include "CloseButton.h"


sf::RectangleShape rectangle_array[100];
sf::RectangleShape* ptr = rectangle_array;

const int lenght_of_array = sizeof(rectangle_array) / sizeof(sf::RectangleShape);

void createRectangles();
void shuffleRectangles();
void swap(int i,int j);
void selectionSort(sf::Window* window,sf::RenderTarget* render_target,Button* button_to_deactivate);
void bubbleSort(sf::Window* window, sf::RenderTarget* render_target, Button* button_to_deactivate);
void insertionSort(sf::Window* window, sf::RenderTarget* render_target, Button* button_to_deactivate);
int partition(sf::Window* window, sf::RenderTarget* render_target, int low, int high);
void subquickSort(sf::Window* window, sf::RenderTarget* render_target, int low, int high);
void quickSort(sf::Window* window, sf::RenderTarget* render_target, Button* button_to_deactivate,int low,int high);
int getMax(int n);
void countSort(sf::Window* window, sf::RenderTarget* render_target, int n, int exp);
void radixSort(sf::Window* window, sf::RenderTarget* render_target, Button* button_to_deactivate, int n);
void flip(sf::Window* window, sf::RenderTarget* render_target,int i);
int findMax(int n);
void pancakeSort(sf::Window* window, sf::RenderTarget* render_target, Button* button_to_deactivate,int n);



CloseButton* close_button;
Button* start_button;
Button* repeat_button;
bool selection_sorted = false;
bool bubble_sorted = false;
bool insertion_sorted = false;
bool quick_sorted = false;
bool radix_sorted=false;
bool pancake_sorted = false;
bool is_main_menu_on = true;
bool is_initialized = false;
sf::Font font;

sf::Event event;
int main()
{
    //Initialize texts and fonts
    sf::Font title_font;
    title_font.loadFromFile("Fonts/ethnocentric rg.otf");
    sf::Text title;
    title.setFont(title_font);
    title.setCharacterSize(30);
    title.setFillColor(sf::Color(68, 252, 243));
    title.setString("SORTING ALGORITHMS");
    title.setOutlineColor(sf::Color::Black);
    title.setOutlineThickness(1);
    title.setPosition(165, 80);
  
    font.loadFromFile("Fonts/timesnewroman.ttf");
       
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(800, 600), "Window", sf::Style::Default);
   
    //Initialize windows title and icon
    window.setTitle("Sorting Algorithms");

    auto image = sf::Image{};
    image.loadFromFile("Textures/icon.png");
    window.setIcon(image.getSize().x,image.getSize().y,image.getPixelsPtr());
    
    //TODO set a proper background
    //sf::Sprite background;
    //sf::Texture background_texture;
    //background_texture.loadFromFile("Textures/background.png");
    //background.setTexture(background_texture); 


    Button selection_sort_button(100.f, 50.f, 200, 175.f, sf::Color(68, 252, 243), "Selection Sort", &font);
    Button bubble_sort_button(100.f, 50.f, 200.f, 275.f, sf::Color(68, 252, 243), "Bubble Sort", &font);
    Button insertion_sort_button(100.f, 50.f, 200.f, 375.f, sf::Color(68, 252, 243), "Insertion Sort", &font);
    Button pancake_sort_button(100.f, 50.f, 500.f, 175.f, sf::Color(68, 252, 243), "Pancake Sort", &font);
    Button quick_sort_button(100.f, 50.f, 500.f, 275.f, sf::Color(68, 252, 243),"Quick Sort",&font);
    Button radix_sort_button(100.f, 50.f, 500.f, 375.f, sf::Color(68, 252, 243),"Radix Sort",&font);

    createRectangles();


    while (window.isOpen()) {


       

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {

                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if (selection_sort_button.isClicked(&event))
                    {
                        selection_sort_button.setIsActive(true);
                        is_main_menu_on = false;

                    }
                    else if (bubble_sort_button.isClicked(&event))
                    {
                        bubble_sort_button.setIsActive(true);
                        is_main_menu_on = false;
                    }
                    else if (insertion_sort_button.isClicked(&event))
                    {
                        insertion_sort_button.setIsActive(true);
                        is_main_menu_on = false;
                    }
                    else if (quick_sort_button.isClicked(&event))
                    {
                        quick_sort_button.setIsActive(true);
                        is_main_menu_on = false;
                    }
                    else if (radix_sort_button.isClicked(&event))
                    {
                        radix_sort_button.setIsActive(true);
                        is_main_menu_on = false;
                    }
                    else if (pancake_sort_button.isClicked(&event))
                    {
                        pancake_sort_button.setIsActive(true);
                        is_main_menu_on = false;
                    }
                }
            }
        }
        if (is_main_menu_on)
        {
            window.clear(sf::Color(255, 255, 255, 255));
            window.draw(title);
            selection_sort_button.draw(&window);
            bubble_sort_button.draw(&window);
            insertion_sort_button.draw(&window);
            quick_sort_button.draw(&window);
            radix_sort_button.draw(&window);
            pancake_sort_button.draw(&window);
            window.display();
 

     
        }

        else if (selection_sort_button.getIsActive())
        {

            selectionSort(&window, &window, &selection_sort_button);

        }
        else if (bubble_sort_button.getIsActive())
        {
            bubbleSort(&window, &window, &bubble_sort_button);
        }
        else if (insertion_sort_button.getIsActive())
        {
            insertionSort(&window, &window, &insertion_sort_button);
        }
        else if (quick_sort_button.getIsActive())
        {
            quickSort(&window, &window, &quick_sort_button, 0, lenght_of_array - 1);
        }
        else if (radix_sort_button.getIsActive())
        {
            radixSort(&window, &window, &radix_sort_button, lenght_of_array);
        }
        else if (pancake_sort_button.getIsActive())
        {
            pancakeSort(&window, &window, &pancake_sort_button, lenght_of_array);
            
        }
           
    }
    return 0;
      

}

void createRectangles()
{
    float xpos = 0;
    for (int i = 0; i < lenght_of_array; i++) {

        if (i == 0) {
            xpos = 0;
        }
        rectangle_array[i].setFillColor(sf::Color::Green);
        rectangle_array[i].setSize(sf::Vector2f(7.f, float(1 + rand() % 400)));
        rectangle_array[i].setOrigin(rectangle_array[i].getLocalBounds().left, rectangle_array[i].getLocalBounds().top + rectangle_array[i].getLocalBounds().height);
        rectangle_array[i].setPosition(sf::Vector2f(xpos, 500));
        xpos += 8;
    }
}

void shuffleRectangles()
{
    for (int i = 0; i < lenght_of_array; i++)
    {
        rectangle_array[i].setSize(sf::Vector2f(7.f, 1 + rand() % 400));
        rectangle_array[i].setOrigin(rectangle_array[i].getLocalBounds().left, rectangle_array[i].getLocalBounds().top + rectangle_array[i].getLocalBounds().height);
    }
}

void swap(int i,int j)
{
    float temp = rectangle_array[i].getSize().y;
    rectangle_array[i].setSize(sf::Vector2f(rectangle_array[i].getSize().x, rectangle_array[j].getSize().y));
    rectangle_array[i].setOrigin(rectangle_array[i].getLocalBounds().left, rectangle_array[i].getLocalBounds().top + rectangle_array[i].getLocalBounds().height);
    rectangle_array[j].setSize(sf::Vector2f(rectangle_array[j].getSize().x, temp));
    rectangle_array[j].setOrigin(rectangle_array[j].getLocalBounds().left, rectangle_array[j].getLocalBounds().top + rectangle_array[j].getLocalBounds().height);
}

void selectionSort(sf::Window* window,sf::RenderTarget* render_target, Button* button_to_deactivate)
{

    if (!is_initialized)
    {
        start_button = new Button(50.f, 50.f, 50.f, 50.f, sf::Color(68, 252, 243), "Start", &font);
        repeat_button = new Button(50.f, 50.f, 200.f, 50.f, sf::Color::Yellow, "Again", &font);
        close_button = new CloseButton(50.f, 50.f, 100.f, 50.f, sf::Color::Red, "Close", &font);
        is_initialized = true;
    }



    if (start_button->isClicked(&event)) {
        start_button->setIsActive(true);
    }


    if (!start_button->getIsActive())
    {
        render_target->clear(sf::Color(255, 255, 255, 255));
        for (int i = 0; i < lenght_of_array; i++) {

            render_target->draw(rectangle_array[i]);

        }
        start_button->draw(render_target);
        window->display();
    }
    else
    {
        if (!selection_sorted)
        {

            for (int i = 0; i < lenght_of_array; i++)
            {


                //holder for the first compared value
                float lenght_temp = rectangle_array[i].getSize().y;
                //index of the minumun value
                int min_index = i;
                for (int j = i + 1; j < lenght_of_array; j++)
                {

                    if (rectangle_array[j].getGlobalBounds().height < rectangle_array[min_index].getGlobalBounds().height)
                    {
                        min_index = j;

                    }

                }

                rectangle_array[i].setSize(sf::Vector2f(rectangle_array[i].getSize().x, rectangle_array[min_index].getSize().y));
                rectangle_array[i].setOrigin(rectangle_array[i].getLocalBounds().left, rectangle_array[i].getLocalBounds().top + rectangle_array[i].getLocalBounds().height);
                rectangle_array[min_index].setSize(sf::Vector2f(rectangle_array[min_index].getSize().x, lenght_temp));
                rectangle_array[min_index].setOrigin(rectangle_array[min_index].getLocalBounds().left, rectangle_array[min_index].getLocalBounds().top + rectangle_array[min_index].getLocalBounds().height);
               
                render_target->clear(sf::Color(255, 255, 255, 255));

                for (int i = 0; i < lenght_of_array; i++) {

                    render_target->draw(rectangle_array[i]);


                }

                window->display();
                sf::sleep(sf::microseconds(10000));



            }
            selection_sorted = true;
        }
        else
        {
            render_target->clear(sf::Color(255, 255, 255, 255));
            for (int i = 0; i < lenght_of_array; i++) {

                render_target->draw(rectangle_array[i]);

            }
            close_button->draw(render_target);
            repeat_button->draw(render_target);

            window->display();
            if (close_button->isClicked(&event))
            {
                close_button->turnOff(button_to_deactivate);
                is_main_menu_on = true;
                selection_sorted = false;
                is_initialized = false;
                start_button->setIsActive(false);
                shuffleRectangles();
                
                delete close_button;
                delete start_button;
                delete repeat_button;
            }
            if (repeat_button->isClicked(&event)) {
                selection_sorted = false;
                shuffleRectangles();
            }
        }
    }
}

void bubbleSort(sf::Window* window, sf::RenderTarget* render_target, Button* button_to_deactivate)
{
    

    if (!is_initialized)
    {
        start_button = new Button(50.f, 50.f, 50.f, 50.f, sf::Color(68, 252, 243), "Start", &font);
         repeat_button = new Button(50.f, 50.f, 200.f, 50.f, sf::Color::Yellow, "Again", &font);
        close_button = new CloseButton(50.f, 50.f, 100.f, 50.f, sf::Color::Red, "Close", &font);
        is_initialized = true;
    }

    if (start_button->isClicked(&event)) {
        start_button->setIsActive(true);
    }
    if (!start_button->getIsActive())
    {
        render_target->clear(sf::Color(255, 255, 255, 255));
        for (int i = 0; i < lenght_of_array; i++) {

            render_target->draw(rectangle_array[i]);

        }
        start_button->draw(render_target);
        window->display();
    }
    else
    {
        if (!bubble_sorted)
        {

            for (int i = 0; i < lenght_of_array; i++)
            {
                for (int j = 0; j < lenght_of_array - i - 1; j++)
                {
                    if (rectangle_array[j].getGlobalBounds().height > rectangle_array[j + 1].getGlobalBounds().height)
                    {

                        swap(j, j + 1);
                    }
                    render_target->clear(sf::Color::White);
                    for (int i = 0; i < lenght_of_array; i++) {

                        render_target->draw(rectangle_array[i]);
                    }

                    window->display();
                    sf::sleep(sf::microseconds(1000));
                }

            }

            bubble_sorted = true;
        }
        else
        {
            render_target->clear(sf::Color(255, 255, 255, 255));
            for (int i = 0; i < lenght_of_array; i++) {

                render_target->draw(rectangle_array[i]);

            }
            close_button->draw(render_target);
            repeat_button->draw(render_target);
            window->display();
            if (close_button->isClicked(&event))
            {
                close_button->turnOff(button_to_deactivate);
                is_main_menu_on = true;
                bubble_sorted = false;
                is_initialized = false;
                start_button->setIsActive(false);
                shuffleRectangles();
                delete close_button;
                delete start_button;
                delete repeat_button;
            }
            if (repeat_button->isClicked(&event)) {
                bubble_sorted = false;
                shuffleRectangles();
            }
        }
    }
}

void insertionSort(sf::Window* window, sf::RenderTarget* render_target, Button* button_to_deactivate)
{
    if (!is_initialized)
    {
        start_button = new Button(50.f, 50.f, 50.f, 50.f, sf::Color(68, 252, 243), "Start", &font);
         repeat_button = new Button(50.f, 50.f, 200.f, 50.f, sf::Color::Yellow, "Again", &font);
        close_button = new CloseButton(50.f, 50.f, 100.f, 50.f, sf::Color::Red, "Close", &font);
        is_initialized = true;
    }

    if (start_button->isClicked(&event)) {
        start_button->setIsActive(true);
    }
    if (!start_button->getIsActive())
    {
        render_target->clear(sf::Color(255, 255, 255, 255));
        for (int i = 0; i < lenght_of_array; i++) {

            render_target->draw(rectangle_array[i]);

        }
        start_button->draw(render_target);
        window->display();
    }
    else {
        if (!insertion_sorted)
        {

            int i, key, j;

            for (i = 1; i < lenght_of_array; i++)
            {
                key = rectangle_array[i].getSize().y;
                j = i - 1;


                while (j >= 0 && rectangle_array[j].getSize().y > key)
                {
                    rectangle_array[j + 1].setSize(sf::Vector2f(rectangle_array[j + 1].getSize().x, rectangle_array[j].getSize().y));
                    rectangle_array[j + 1].setOrigin(rectangle_array[j + 1].getLocalBounds().left, rectangle_array[j + 1].getLocalBounds().top + rectangle_array[j + 1].getLocalBounds().height);
                    j = j - 1;
                    render_target->clear(sf::Color::White);
                    for (int i = 0; i < lenght_of_array; i++) {

                        render_target->draw(rectangle_array[i]);
                    }
                    window->display();
                    sf::sleep(sf::microseconds(10000));

                }
                rectangle_array[j + 1].setSize(sf::Vector2f(rectangle_array[j + 1].getSize().x, key));
                rectangle_array[j + 1].setOrigin(rectangle_array[j + 1].getLocalBounds().left, rectangle_array[j + 1].getLocalBounds().top + rectangle_array[j + 1].getLocalBounds().height);
                render_target->clear(sf::Color::White);
                for (int i = 0; i < lenght_of_array; i++) {

                    render_target->draw(rectangle_array[i]);
                }
                window->display();
                sf::sleep(sf::microseconds(10000));
            }
            insertion_sorted = true;
        }
        else
        {
            render_target->clear(sf::Color(255, 255, 255, 255));
            for (int i = 0; i < lenght_of_array; i++) {

                render_target->draw(rectangle_array[i]);

            }
            close_button->draw(render_target);
            repeat_button->draw(render_target);
            window->display();
            if (close_button->isClicked(&event))
            {
                close_button->turnOff(button_to_deactivate);
                is_main_menu_on = true;
                insertion_sorted = false;
                is_initialized = false;
                start_button->setIsActive(false);
                shuffleRectangles();
                delete close_button;
                delete start_button;
                delete repeat_button;
            }
            if (repeat_button->isClicked(&event)) {
                insertion_sorted = false;
                shuffleRectangles();
            }
        }
    }
}

int partition(sf::Window* window, sf::RenderTarget* render_target, int low, int high)
{
    int pivot = rectangle_array[high].getSize().y;
    int i = (low - 1);

    for (int j = low; j <= high-1; j++) {
        if (rectangle_array[j].getSize().y < pivot) {
            i++;
            swap(i, j);


            //render
            render_target->clear(sf::Color::White);
            for (int i = 0; i < lenght_of_array; i++) {

                render_target->draw(rectangle_array[i]);
            }
            window->display();
            sf::sleep(sf::microseconds(10000));
        }
    }
    swap(i + 1, high);

    //render
    render_target->clear(sf::Color::White);
    for (int i = 0; i < lenght_of_array; i++) {

        render_target->draw(rectangle_array[i]);
    }
    window->display();
    sf::sleep(sf::microseconds(10000));


    return i+1;
}


void subquickSort(sf::Window* window, sf::RenderTarget* render_target, int low, int high)
{
    if (low < high)
    {
        int pi = partition(window, render_target, low, high);



        subquickSort(window, render_target, low, pi - 1);
        subquickSort(window, render_target, pi + 1, high);

    }
}
void quickSort(sf::Window * window, sf::RenderTarget * render_target, Button * button_to_deactivate, int low, int high)
{
    if (!is_initialized)
    {
        start_button = new Button(50.f, 50.f, 50.f, 50.f, sf::Color(68, 252, 243), "Start", &font);
         repeat_button = new Button(50.f, 50.f, 200.f, 50.f, sf::Color::Yellow, "Again", &font);
        close_button = new CloseButton(50.f, 50.f, 100.f, 50.f, sf::Color::Red, "Close", &font);
        is_initialized = true;
    }

    if (start_button->isClicked(&event)) {
        start_button->setIsActive(true);
    }
    if (!start_button->getIsActive())
    {
        render_target->clear(sf::Color(255, 255, 255, 255));
        for (int i = 0; i < lenght_of_array; i++) {

            render_target->draw(rectangle_array[i]);

        }
        start_button->draw(render_target);
        window->display();
    }
    else
    {
        if (!quick_sorted)
        {
            

            subquickSort(window, render_target, low, high);

            quick_sorted = true;
        }

        if (quick_sorted)
        {
            render_target->clear(sf::Color(255, 255, 255, 255));
            for (int i = 0; i < lenght_of_array; i++) {

                render_target->draw(rectangle_array[i]);

            }
            close_button->draw(render_target);
            repeat_button->draw(render_target);
            window->display();
            if (close_button->isClicked(&event))
            {
                close_button->turnOff(button_to_deactivate);
                is_main_menu_on = true;
                quick_sorted = false;
                is_initialized = false;
                start_button->setIsActive(false);
                shuffleRectangles();
                delete close_button;
                delete start_button;
                delete repeat_button;
            }
            if (repeat_button->isClicked(&event)) {
                quick_sorted = false;
                shuffleRectangles();
            }
        }
    }
}

int getMax(int n)
{
    int mx = rectangle_array[0].getSize().y;
    for (int i = 1; i < n; i++)
    {
        if (rectangle_array[i].getSize().y > mx)
            mx = rectangle_array[i].getSize().y;
    }
    return mx;
}

void countSort(sf::Window* window, sf::RenderTarget* render_target, int n , int exp)
{
    int output[lenght_of_array] = { 0 };
    int i, count[10] = { 0 };
    for (i = 0; i < n; i++)
        count[int(rectangle_array[i].getSize().y / exp) % 10]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--) {
        output[count[int(rectangle_array[i].getSize().y / exp) % 10] - 1] = rectangle_array[i].getSize().y;
        count[(int(rectangle_array[i].getSize().y / exp) % 10)]--;
    }
    for (i = 0; i < n; i++) {
        rectangle_array[i].setSize(sf::Vector2f(rectangle_array[i].getSize().x, output[i]));
        rectangle_array[i].setOrigin(rectangle_array[i].getLocalBounds().left, rectangle_array[i].getLocalBounds().top + rectangle_array[i].getLocalBounds().height);
        render_target->clear(sf::Color::White);
        for (int i = 0; i < lenght_of_array; i++) {

            render_target->draw(rectangle_array[i]);
        }
        window->display();
        sf::sleep(sf::microseconds(10000));
    }

}

void radixSort(sf::Window* window, sf::RenderTarget* render_target, Button* button_to_deactivate, int n)
{
    if (!is_initialized)
    {
        start_button = new Button(50.f, 50.f, 50.f, 50.f, sf::Color(68, 252, 243), "Start", &font);
         repeat_button = new Button(50.f, 50.f, 200.f, 50.f, sf::Color::Yellow, "Again", &font);
        close_button = new CloseButton(50.f, 50.f, 100.f, 50.f, sf::Color::Red, "Close", &font);
        is_initialized = true;
    }
   
    if (start_button->isClicked(&event)) {
        start_button->setIsActive(true);
    }
    if (!start_button->getIsActive())
    {
        
        render_target->clear(sf::Color(255, 255, 255, 255));
        for (int i = 0; i < lenght_of_array; i++) {

            render_target->draw(rectangle_array[i]);

        }
        start_button->draw(render_target);
        window->display();
    }
    else
    {
        if (!radix_sorted) {
            
            int m = getMax(n);

            render_target->clear(sf::Color(255, 255, 255, 255));
            for (int exp = 1; m / exp > 0; exp *= 10)
            {
                countSort(window, render_target, n, exp);

            }
            radix_sorted = true;
        }
        else
        {
            render_target->clear(sf::Color(255, 255, 255, 255));
            for (int i = 0; i < lenght_of_array; i++) {

                render_target->draw(rectangle_array[i]);

            }
            close_button->draw(render_target);
            repeat_button->draw(render_target);
            window->display();
            if (close_button->isClicked(&event))
            {
                close_button->turnOff(button_to_deactivate);
                is_main_menu_on = true;
                radix_sorted = false;
                is_initialized = false;
                start_button->setIsActive(false);
                shuffleRectangles();
                delete close_button;
                delete start_button;
                delete repeat_button;
            }
            if (repeat_button->isClicked(&event)) {
                radix_sorted = false;
                shuffleRectangles();
            }
        }
    }
}
void flip(sf::Window* window, sf::RenderTarget* render_target,int i)
{
    int start = 0;
    while (start < i)
    {
        swap(start, i);
        render_target->clear(sf::Color(255, 255, 255, 255));

        for (int i = 0; i < lenght_of_array; i++) {

            render_target->draw(rectangle_array[i]);


        }

        window->display();
        sf::sleep(sf::microseconds(10000));
        start++;
        i--;
    }
}




int findMax(int n)
{
    int mi, i;
    for (mi = 0, i = 0; i < n; ++i)
        if (rectangle_array[i].getSize().y > rectangle_array[mi].getSize().y)
            mi = i;
    return mi;
}
void pancakeSort(sf::Window* window, sf::RenderTarget* render_target, Button* button_to_deactivate, int n)
{
    if (!is_initialized)
    {
 start_button = new Button(50.f, 50.f, 50.f, 50.f, sf::Color(68, 252, 243), "Start", &font);
         repeat_button = new Button(50.f, 50.f, 200.f, 50.f, sf::Color::Yellow, "Again", &font);
        close_button = new CloseButton(50.f, 50.f, 100.f, 50.f, sf::Color::Red, "Close", &font);
        is_initialized = true;
    }
    if (start_button->isClicked(&event)) {
        start_button->setIsActive(true);
    }
    if (!start_button->getIsActive())
    {
        render_target->clear(sf::Color(255, 255, 255, 255));
        for (int i = 0; i < lenght_of_array; i++) {

            render_target->draw(rectangle_array[i]);

        }
        start_button->draw(render_target);
        window->display();
    }
    else
    {
        if (!pancake_sorted) {
            


            for (int curr_size = n; curr_size > 1; --curr_size)
            {
                int mi = findMax(curr_size);

                if (mi != curr_size - 1)
                {
                    flip(window,render_target,mi);

                    flip(window,render_target,curr_size - 1);
                }

            }
            pancake_sorted = true;
        }
        else
        {
            render_target->clear(sf::Color(255, 255, 255, 255));
            for (int i = 0; i < lenght_of_array; i++) {

                render_target->draw(rectangle_array[i]);

            }

            close_button->draw(render_target);
            repeat_button->draw(render_target);
            window->display();
            if (close_button->isClicked(&event))
            {
                close_button->turnOff(button_to_deactivate);
                is_main_menu_on = true;
                pancake_sorted = false;
                is_initialized = false;
                start_button->setIsActive(false);
                shuffleRectangles();
                delete close_button;
                delete start_button;
                delete repeat_button;
            }
            if (repeat_button->isClicked(&event)) {
                pancake_sorted = false;
                shuffleRectangles();
            }
        }
    }
}

