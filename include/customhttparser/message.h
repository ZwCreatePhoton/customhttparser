#include <memory>

#include "http.h"


namespace HTTP
{
    class Message
    {
        public:
            State state();
            void set_state(State state);

            bool is_request();
            bool is_response();

            StartLine &start_line();
            void add_start_line(std::unique_ptr<StartLine> startLine);

            void add_header(std::unique_ptr<Header> header);
            void add_header(const std::string& name, const std::string& value);
            std::vector<std::reference_wrapper<Header>> headers();

            void append_body_data(const std::string& body_data);
            std::string &body(); // raw; not normalized

            std::vector<Chunk> &chunks();

            std::string normalized_body(bool chunking = true);

            bool _is_request = false;

        private:
            State _state = State::UNKNOWN;
            std::unique_ptr<StartLine> _start_line = std::make_unique<StartLine>();
            std::vector<std::unique_ptr<Header>> _headers{};
            std::string _body{};
            std::vector<Chunk> _chunks{};
    };

}
