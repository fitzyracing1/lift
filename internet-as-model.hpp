// internet-as-model.hpp
// Treat the open internet (or any specific URL) as an ai::Model
//
// Depends on the core interface from ai-iface (or copy the Model base here).
// This header focuses only on the web / internet backend.

#ifndef INTERNET_AS_MODEL_HPP
#define INTERNET_AS_MODEL_HPP

#include <string>
#include <memory>
#include <functional>
#include <cctype>

// If you already have the core header:
// #include "ai-iface.hpp"
//
// Otherwise the minimal Model base is repeated below so this file
// can stand alone while you decide how to structure the two repos.

#ifndef AI_IFACE_HPP
namespace ai {
class Model {
public:
    virtual ~Model() = default;
    virtual std::string infer(const std::string& prompt,
                              const std::string& system = "") = 0;
    virtual void infer_stream(const std::string& prompt,
                              std::function<void(const std::string&)> on_token,
                              const std::string& system = "") {
        on_token(infer(prompt, system));
    }
    virtual std::string name() const { return "unnamed"; }
    virtual bool is_ready() const { return true; }
};
} // namespace ai
#endif

namespace ai {

/**
 * InternetModel
 *
 * Turns any URL (or the special name "internet") into a Model.
 * The real implementation should perform HTTP, scrape, or call a web agent.
 * The stub below keeps the header zero-dependency and compilable today.
 */
class InternetModel : public Model {
    std::string endpoint_;

public:
    explicit InternetModel(std::string endpoint) : endpoint_(std::move(endpoint)) {}

    std::string infer(const std::string& prompt,
                      const std::string& system = "") override {
        // TODO: real HTTP / agent call goes here
        std::string msg = "[internet] target=" + endpoint_ + "\n";
        if (!system.empty()) msg += "system: " + system + "\n";
        msg += "prompt: " + prompt + "\n";
        msg += "(stub – replace with real network call)";
        return msg;
    }

    std::string name() const override {
        return endpoint_.empty() ? "internet" : endpoint_;
    }
};

inline bool looks_like_url(const std::string& s) {
    if (s.size() < 8) return false;
    auto lower = s;
    for (char& c : lower) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return lower.rfind("http://", 0) == 0 || lower.rfind("https://", 0) == 0;
}

/**
 * Convenience factory for the internet side
 *
 *   auto net  = ai::create_internet();                    // whole internet
 *   auto site = ai::create_internet("https://example.com");
 */
inline std::unique_ptr<Model> create_internet(const std::string& target = "internet") {
    if (target.empty() || target == "internet" || target == "web" || target == "net") {
        return std::make_unique<InternetModel>("internet");
    }
    if (looks_like_url(target)) {
        return std::make_unique<InternetModel>(target);
    }
    return std::make_unique<InternetModel>(target); // treat as opaque endpoint name
}

} // namespace ai

#endif // INTERNET_AS_MODEL_HPP
