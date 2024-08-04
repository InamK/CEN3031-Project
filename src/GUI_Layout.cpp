#include "GUI_Layout.h"

void GUI::RunGUI() {
        //Code copied from ImGui demo
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen) {
            const ImGuiViewport *viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                            ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        } else {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", nullptr, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO &io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }
        // End of copied code
        // Switch case for pages
        ImGui::Begin("Library");
        switch (page) {
            case 0:
                calendar();
            case 1:
                Date();
            case 2:
                Home();
            case 3:
                Books();
            case 4:
                Events();
            case 5:
                CreateResource();
            case 6:
                Members();
            case 7:
                Event_Create();
            case 8:
                Confirmations();
        }
        ImGui::End();
        // Buttons for navigation menu. Some are only visible for employees/Admins
        ImGui::Begin("Navigation");
        if(!login){
            if(ImGui::Button("Login/Signup")){
                page = 2;
            }
        }
        if(ImGui::Button("Resources")){
            page = 3;
        }
        if(employee || admin){
            if(ImGui::Button("Add Resource")){
                page = 5;
            }
            if(ImGui::Button("Checkout/Return Confirmations")){
                page = 8;
            }
        }
        if(ImGui::Button("Calendar")){
            page = 0;
        }
        if(admin){
            if(ImGui::Button("Account Management")){
                page = 6;
            }
            if(ImGui::Button("Event Approvals")){
                page = 4;
            }
        }
        ImGui::End();
        ImGui::End();
        //ImGui::ShowDemoWindow();
    }

GUI::GUI(UserManager& users, EventManager& events, BookManager& books) : users(users), events(events), books(books){
    //Get current year and month
    std::time_t t = std::time(nullptr);
    std::tm *now = std::localtime(&t);
    year = now->tm_year + 1900; // tm_year is years since 1900
    month = now->tm_mon + 1;    // tm_mon is 0-based (0 = January)
}

void GUI::calendar() {
    // Variables for the calendar
    const int daysInWeek = 7;
    const ImVec2 cellSize = ImVec2(70, 70);
    const float cellPadding = 7.0f;

    // Display month and year selector
    ImGui::InputInt("Year", &year);
    ImGui::InputInt("Month", &month);

    // Clamp the month value to be between 1 and 12
    if (month < 1) {
        month = 12;
        year--;
    }
    if (month > 12) {
        month = 1;
        year++;
    }

    // Calculate the number of days in the selected month
    int daysInMonth = 31; // Default to 31 days
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        daysInMonth = 30;
    } else if (month == 2) {
        // Check for leap year
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        daysInMonth = isLeapYear ? 29 : 28;
    }

    // Calculate the starting day of the month (0 = Sunday, 6 = Saturday)
    tm time_in = {0, 0, 0, 1, month - 1, year - 1900}; // Note: tm_mon is 0-based, tm_year is year since 1900
    time_t time_temp = mktime(&time_in);
    const tm *time_out = localtime(&time_temp);
    int startDay = time_out->tm_wday;

    // Get the draw list for custom drawing
    ImDrawList *draw_list = ImGui::GetWindowDrawList();
    ImVec2 windowPos = ImGui::GetCursorScreenPos();
    ImVec2 startPos = windowPos;

    // Display day labels
    const char *daysOfWeek[] = {"    Sun", "      Mon", "       Tue", "       Wed", "       Thu", "       Fri",
                                "       Sat"};
    for (int i = 0; i < daysInWeek; ++i) {
        ImGui::Text("%s", daysOfWeek[i]);
        if (i < daysInWeek - 1) ImGui::SameLine();
    }

    // Calculate the starting position for the calendar grid
    ImVec2 calendarStartPos = ImGui::GetCursorScreenPos();
    int rows = int(std::ceil((float(daysInMonth) - (7 - float(startDay))) / float(daysInWeek)) + 1);
    // Draw horizontal grid lines and the border
    for (int i = 0; i <= rows; ++i) {
        float Padding = cellPadding;
        if (i != 0) {
            Padding = 3 * cellPadding;
        }
        ImVec2 lineStart = ImVec2(calendarStartPos.x, calendarStartPos.y + float(i) * (cellSize.y + Padding));
        ImVec2 lineEnd = ImVec2(calendarStartPos.x + daysInWeek * (cellSize.x + cellPadding),
                                calendarStartPos.y + float(i) * (cellSize.y + Padding));
        draw_list->AddLine(lineStart, lineEnd, IM_COL32(200, 200, 200, 255));
    }

    // Draw vertical grid lines and the border
    for (int i = 0; i <= daysInWeek; ++i) {
        float VPadding = 3 * cellPadding;
        float Padding = 0;
        if (i != 0) {
            Padding = cellPadding;
        }
        ImVec2 lineStart = ImVec2(calendarStartPos.x + float(i) * (cellSize.x + Padding), calendarStartPos.y);
        ImVec2 lineEnd = ImVec2(calendarStartPos.x + float(i) * (cellSize.x + Padding),
                                calendarStartPos.y + float(rows) * (cellSize.y + VPadding));
        draw_list->AddLine(lineStart, lineEnd, IM_COL32(200, 200, 200, 255));
    }

    // Draw cells for days
    ImGui::Dummy(ImVec2(0.0f, 0.0f));
    for (int i = 0; i < startDay; ++i) {
        ImGui::Dummy(cellSize); // Empty cell for days before the start of the month
        if (i < daysInWeek - 1) ImGui::SameLine();
    }

    for (int i = 1; i <= daysInMonth; ++i) {
        if ((i + startDay - 1) % daysInWeek != 0) {
            ImGui::SameLine();
        } else if (i > 1) {
            ImGui::NewLine();
        }
        if(ImGui::Button(std::to_string(i).c_str(), cellSize)){
            day = i;
            page = 1;
        }
    }
}

void GUI::Date() {
    if(page == 1) {
        std::string date;
        switch (month) {
            case 1:
                date = "January";
                break;
            case 2:
                date = "February";
                break;
            case 3:
                date = "March";
                break;
            case 4:
                date = "April";
                break;
            case 5:
                date = "May";
                break;
            case 6:
                date = "June";
                break;
            case 7:
                date = "July";
                break;
            case 8:
                date = "August";
                break;
            case 9:
                date = "September";
                break;
            case 10:
                date = "October";
                break;
            case 11:
                date = "November";
                break;
            case 12:
                date = "December";
                break;
        }
        std::string suffix;
        int digit = day % 10;
        if (digit == 1 && day != 11) {
            suffix = "st";
        } else if (digit == 2 && day != 12) {
            suffix = "nd";
        } else if (digit == 3 && day != 13) {
            suffix = "rd";
        } else {
            suffix = "th";
        }
        date = date + " " + std::to_string(day) + suffix + ", " + std::to_string(year);
        char *charArray = new char[date.length() + 1];
        std::strcpy(charArray, date.c_str());
        ImGui::Text("%s", charArray);
        ImGui::Button("RSVP");
        delete[] charArray;
        if (employee) {
            if (ImGui::Button("Add Event")) {
                page = 7;
            }
        }
    }
}

void GUI::Home() {
    if(page == 2) {
        // Declare variables to hold input
        static char username[128] = "";
        static char password[128] = "";
        std::string role;
        static bool login_failed = false;
        // Input fields for the username and password
        ImGui::InputText("Username", username, IM_ARRAYSIZE(username));
        ImGui::InputText("Password", password, IM_ARRAYSIZE(password), ImGuiInputTextFlags_Password);
        // Button for the login action
        if (ImGui::Button("Login")) {
            //Password hash
            int total = 0;
            std::string pass = password;
            for (int i = 0; i < pass.length(); ++i) {
                int asciiValue = static_cast<int>(pass[i]);
                int position = i + 1; // 1-based index
                total += asciiValue * position;
            }
            pass = std::to_string(total);
            // Example authentication check
            users.validateUser(username, pass);
            if (users.login(username, pass, role)) {
                // Login successful
                login = true;
                login_failed = false;
                if(role != "0"){
                    if(role == "2"){
                        admin = true;
                    }
                    employee = true;
                }
                page = 3;
            } else {
                // Login failed
                login_failed = true;
            }
        }
        // Button for the sign-up action
        ImGui::SameLine();
        if(ImGui::Button("Sign Up")){
            //Password Hash
            role = "0";
            int total = 0;
            std::string pass = password;
            for (int i = 0; i < pass.length(); ++i) {
                int asciiValue = static_cast<int>(pass[i]);
                int position = i + 1; // 1-based index
                total += asciiValue * position;
            }
            pass = std::to_string(total);
            if (users.createAccount(username, pass, role)) {
                users.validateUser(username, pass);
                // Login successful
                login = true;
                login_failed = false;
                page = 3;
            } else {
                // Login failed
                login_failed = true;
            }
        }
        // Display a message if login failed
        if (login_failed) {
            ImGui::TextColored(ImVec4(1, 0, 0, 1), "Login or Sign Up failed! Please try again.");
        }
        if(ImGui::Button("Debug")){
            login = true;
            admin = true;
            employee = true;
        }
    }
}

void GUI::Books() {
    if(page == 3){
        static int index = 0;
        static int index_end = 10;
        static char query[255] = "";
        ImGui::InputText("Title/Author", query, IM_ARRAYSIZE(query));
        //Dropdown for resource type
        const char* items[] = { "Any" ,"Book", "DVD"};
        static int currentItem = 0; // Index of the currently selected item
        // Create a combo box (drop-down menu)
        if (ImGui::BeginCombo("Resource Type", items[currentItem])){
            // Loop through all items
            for (int n = 0; n < IM_ARRAYSIZE(items); n++){
                // Check if the item is selected
                bool isSelected = (currentItem == n);
                // Display the item
                if (ImGui::Selectable(items[n], isSelected)){
                    currentItem = n; // Update the selected item
                }
                // Set the initial focus when opening menu
                if (isSelected){
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
        //Dropdown for genre
        const char* genres[] = { "Any" ,"Horror", "Fantasy", "Sci-Fi", "Nonfiction", "Mystery", "Thriller", "Self Help", "Romance"};
        static int genre = 0; // Index of the currently selected item
        // Create a combo box (drop-down menu)
        if (ImGui::BeginCombo("Genre", genres[genre])){
            // Loop through all items
            for (int n = 0; n < IM_ARRAYSIZE(genres); n++){
                // Check if the item is selected
                bool isSelected = (genre == n);
                // Display the item
                if (ImGui::Selectable(genres[n], isSelected)){
                    genre = n; // Update the selected item
                }
                // Set the initial focus when opening menu
                if (isSelected){
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
        std::vector<std::vector<std::string>> all;
        if(query != ""){
            all = books.searchBooks(query);
        } else{
            all = books.getAllBooks();
        }
        int total = all.size();
        if(ImGui::Button("Previous")){
            if((index - 10) >= 0){
                index -= 10;
            }
        }
        ImGui::SameLine();
        if(ImGui::Button("Next")){
            if((index + 10) < total){
                index += 10;
            }
        }
        index_end = index + 10;
        if(index_end > total){
            index_end = total;
        }
        std::vector<Book> all_books;
        for(int i = index; i < index_end; i++){
            Book temp = Book(all[i][0], all[i][1], all[i][2], all[i][3], all[i][4]);
            all_books.push_back(temp);
//            if(genre == 0 && currentItem == 0) {
//                all_books.push_back(temp);
//            }
        }
        std::vector<std::string> titles;
        titles.emplace_back("Title:");
        std::vector<std::string> authors;
        authors.emplace_back("Author:");
        for(Book i : all_books){
            titles.push_back(i.title);
            authors.push_back(i.author);
        }
        size_t maxLength = 0;
        for (const auto& str : titles) {
            maxLength = std::max(maxLength, str.length());
        }
        maxLength++;
        // Add spaces to the end of each string to make them all the same length
        for (auto& str : titles) {
            if (str.length() < maxLength) {
                str.append(maxLength - str.length(), ' ');
            }
        }
        maxLength = 0;
        for (const auto& str : authors) {
            maxLength = std::max(maxLength, str.length());
        }
        maxLength++;
        // Add spaces to the end of each string to make them all the same length
        for (auto& str : authors) {
            if (str.length() < maxLength) {
                str.append(maxLength - str.length(), ' ');
            }
        }
        bool first = true;
        for(int j = 0; j < titles.size(); j++){
            char *charArray = new char[titles[j].length() + 1];
            std::strcpy(charArray, titles[j].c_str());
            ImGui::Text("%s", charArray);
            ImGui::SameLine();
            char *charArray2 = new char[authors[j].length() + 1];
            std::strcpy(charArray2, authors[j].c_str());
            ImGui::Text("%s", charArray2);
            if(first){
                first = false;
            } else {
                if(all_books[j - 1].avalible) {
                    ImGui::SameLine();
                    if(ImGui::Button("Borrow")){

                    }
                }
                if(employee){
                    if(ImGui::Button("Delete")){

                    }
                }
            }
        }
    }
}

void GUI::Events() {
    if(page == 4){
        // Display month and year selector
        ImGui::InputInt("Year", &year);
        ImGui::InputInt("Month", &month);

        // Clamp the month value to be between 1 and 12
        if (month < 1) {
            month = 12;
            year--;
        }
        if (month > 12) {
            month = 1;
            year++;
        }
        //All unapproved events
        //By month?
    }
}


void GUI::CreateResource() {
    if(page == 5){
        //Enterable information for new book
        static char query[255] = "";
        static char author[255] = "";
        ImGui::InputText("Title", query, IM_ARRAYSIZE(query));
        ImGui::InputText("Author", author, IM_ARRAYSIZE(author));
        //Dropdown for resource type
        const char* items[] = { "Book", "DVD"};
        static int currentItem = 0; // Index of the currently selected item
        // Create a combo box (drop-down menu)
        if (ImGui::BeginCombo("Resource Type", items[currentItem])){
            // Loop through all items
            for (int n = 0; n < IM_ARRAYSIZE(items); n++){
                // Check if the item is selected
                bool isSelected = (currentItem == n);
                // Display the item
                if (ImGui::Selectable(items[n], isSelected)){
                    currentItem = n; // Update the selected item
                }
                // Set the initial focus when opening menu
                if (isSelected){
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
        //Dropdown for genre
        const char* genres[] = { "Horror", "Fantasy", "Sci-Fi", "Nonfiction", "Mystery", "Thriller", "Self Help", "Romance"};
        static int genre = 0; // Index of the currently selected item
        // Create a combo box (drop-down menu)
        if (ImGui::BeginCombo("Genre", genres[genre])){
            // Loop through all items
            for (int n = 0; n < IM_ARRAYSIZE(genres); n++){
                // Check if the item is selected
                bool isSelected = (genre == n);
                // Display the item
                if (ImGui::Selectable(genres[n], isSelected)){
                    genre = n; // Update the selected item
                }
                // Set the initial focus when opening menu
                if (isSelected){
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
        if(ImGui::Button("Add") && query != "" && author != ""){
            books.addBook(query, author, "");
        }
    }
}

void GUI::Members() {
    if(page == 6){
        std::vector<std::string> users;
        users.emplace_back("Username ");
        // Find the maximum length of the strings
        size_t maxLength = 0;
        for (const auto& str : users) {
            maxLength = std::max(maxLength, str.length());
        }

        // Add spaces to the end of each string to make them all the same length
        for (auto& str : users) {
            if (str.length() < maxLength) {
                str.append(maxLength - str.length(), ' ');
            }
        }
        bool first = true;
        for(const auto& str : users) {
            char *charArray = new char[str.length() + 1];
            std::strcpy(charArray, str.c_str());
            ImGui::Text("%s", charArray);
            ImGui::SameLine();
            if(first){
                ImGui::Text("%s", "Role     Actions");
                first = false;
            } else {
                if(true){
                    ImGui::Text("%s", "Member   ");
                    ImGui::SameLine();
                    if(ImGui::Button("Hire")){

                    }
                } else if(true){
                    ImGui::Text("%s", "Employee ");
                    ImGui::SameLine();
                    if(ImGui::Button("Fire")){

                    }
                    ImGui::SameLine();
                    if(ImGui::Button("Make Admin")){

                    }
                } else {
                    ImGui::Text("%s", "Admin    ");
                    ImGui::SameLine();
                    if(ImGui::Button("Remove Admin")){

                    }
                }
            }
        }
    }
}

void GUI::Event_Create() {
    if(page == 7){
        std::string date;
        switch (month) {
            case 1:
                date = "January";
                break;
            case 2:
                date = "February";
                break;
            case 3:
                date = "March";
                break;
            case 4:
                date = "April";
                break;
            case 5:
                date = "May";
                break;
            case 6:
                date = "June";
                break;
            case 7:
                date = "July";
                break;
            case 8:
                date = "August";
                break;
            case 9:
                date = "September";
                break;
            case 10:
                date = "October";
                break;
            case 11:
                date = "November";
                break;
            case 12:
                date = "December";
                break;
        }
        std::string suffix;
        int digit = day % 10;
        if (digit == 1 && day != 11) {
            suffix = "st";
        } else if (digit == 2 && day != 12) {
            suffix = "nd";
        } else if (digit == 3 && day != 13) {
            suffix = "rd";
        } else {
            suffix = "th";
        }
        date = date + " " + std::to_string(day) + suffix + ", " + std::to_string(year);
        char *charArray = new char[date.length() + 1];
        std::strcpy(charArray, date.c_str());
        ImGui::Text("%s", charArray);
        static char title [128] = "";
        static char desc[1024] = "";
        ImGui::InputText("Event Title", title, IM_ARRAYSIZE(title));
        ImGui::InputText("Event Description", desc, IM_ARRAYSIZE(desc));
    }
}

void GUI::Confirmations() {
    if(page == 8){
        //transactions 
    }
}
