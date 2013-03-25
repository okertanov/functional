//
// Недавно пристально посмотрел на С++ Variadic Templates
// и неожиданно для себя изобрел новый RAII Scoped Resource Manager.
//
// Получилось кратко и эффектно. Например, с C-style выделением памяти:
//
// Аллоцируем ресурс в блоке.
{
    ha::scoped_resource<void*, size_t> mem(::malloc, 1, ::free);

    ::memset(mem, 65, 1);
}
// А при выходе из блока ресурс будет освобожден автоматически.

// Или еще вот так можно захватывать владение ресурсом "файловый дескриптор":

// Захватываем ресурс в блоке.
{
    ha::scoped_resource<int> fd(
        [&filename]()
        {
            return ::open(filename.c_str(), O_RDONLY);
        },
        ::close);

    assert(fd != -1);

    std::vector<char> buff(1024);
    ssize_t rc = ::read(fd, &buff[0], 1024);
}
// А при выходе из блока ресурс будет освобожден автоматически
// даже после вызова, например, throw std::exception().

// Или второй пример можно переписать даже понятней
// без применения лямбды:

{
    ha::scoped_resource<int, char*, int> fd(::open, filename.c_str(), O_RDONLY, ::close);

    if (fd == -1)
        throw std::runtime_error(std::string("open() failed: ") + ::strerror(errno));

    std::vector<char> buff(1024);
    ssize_t rc = ::read(fd, &buff[0], 1024);
}

//
// То есть в общем случае имеем темплейтный класс,
// который инстанциируется типом ресурса,
// а его конструктор принимает две std::functions:
// initializer_t и finalizer_t.
//
// Между инициализатором и финализатором следуют параметры
// для инициализатора, которые являются частью спецификаторов шаблона.
//
// Деструктор просто вызывает финализатор для захваченного ресурса.
//
// Для raw-доступа к ресурсу существует оператор типа ресурса.
//

{
    ha::scoped_resource
        <resource_t, param1_t, ...>
            resource
                (ititializer, param1, ..., finalizer);

    resource_t
        plain_resource =
            resource.operator resource_t();
}

//
// В чем преимущество перед другими RAII реализациями враперов ресурсов?
//    1. Инициализатор не вызывается во время редукции параметров конструктора,
//       а в самом конструкторе.
//       Это, например, позволяет реализовать "нормальную" передачу инициализатора,
//       что дает возможность захвата ресурса в lazy-стиле, до первого вызова operator resource_t().
//       Еще это позволяет создавать именованные инициализаторы, тем самым переиспользуя их.
//    2. Можно явно передавать какое-либо количество параметров для инициализатора.
//       Тут, возможно, есть еще второй полезный механизм - std::initializer_list.
//    3. Если пункт 2. по каким-то причинам не применим, можно в качестве инициализатора
//       передавать лямбду, которая замкнет все параметры инициализатора на себя.
//    4. Деинициализатор имеет единственный параметр - тип ресурса,
//       но в случае необходимости также может быть лямбдой, замыкая
//       на себя дополнительные параметры деинициализации.
//    5. Это намного проще в реализации чем std::shared_ptr(T* ptr, deleter d).
//

//
// Недостатки?
//     Иногда все же эффективней написать полноценный врапер ресурса.
//

//
// Нужно больше примеров? Их есть у меня:
//

// Создание AVFormatContext контекста:
ha::scoped_resource<ffmpeg::AVFormatContext*> formatctx
    (ffmpeg::avformat_alloc_context, ffmpeg::avformat_free_context);

// Это есть аналог следующего:
std::shared_ptr<ffmpeg::AVFormatContext> formatctx =
    std::shared_ptr<ffmpeg::AVFormatContext>
        (ffmpeg::avformat_alloc_context(), ffmpeg::avformat_free_context);


// Или вот еще, тут применяется составной деинициализатор:
ha::scoped_resource<ffmpeg::AVCodecContext*> codecctx(
        ffmpeg::avcodec_alloc_context,
        [](ffmpeg::AVCodecContext* c)
        {
            ffmpeg::avcodec_close(c),
                ffmpeg::av_free(c);
        });

// А этот пример интересен тем, что происходит захват ресурса, который не нужно освобождать:
ha::scoped_resource<ffmpeg::AVCodec*, ffmpeg::AVCodecID> codec(
        ffmpeg::avcodec_find_decoder,
        codecctx->codec_id,
        [](__attribute__((unused)) ffmpeg::AVCodec* c)
        {
        });

// И наконец самый простой oneliner:
ha::scoped_resource<ffmpeg::AVFrame*> frame(ffmpeg::avcodec_alloc_frame, ffmpeg::av_free);

// Который аналог следующего:
std::shared_ptr<ffmpeg::AVFrame> frame =
    std::shared_ptr<ffmpeg::AVFrame>(ffmpeg::avcodec_alloc_frame(), ffmpeg::av_free);

// Но неужели это все про naked plain-C ресурсы? А где же примеры с годным С++?
// А вот:

ha::mutex mutex;

ha::scoped_resource<ha::mutex*, ha::mutex*> scoped_lock(
    [](ha::mutex* m) -> ha::mutex*
    {
        return m->lock(), m;
    },
    &mutex,
    [](ha::mutex* m) -> void
    {
        m->unlock();
    }
);

//
// Хорошо, но где же реализация?
//     Реализация класса scoped_resource настолько проста и элегантна,
//     что даже чем-то напомнила мне идею Y-combinator.
//     То есть возможно с легкостью реализовать что-то подобное, просто начав с декларации
//     конструктора scoped_resource::scoped_resource(initializer_t, finalizer_t);
//     и затем наращивать variadic-часть для параметров.
//

//
// Вот как-то так.
// © 2013 okertanov@gmail.com
//

