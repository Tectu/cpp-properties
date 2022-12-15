#pragma once

namespace gpds
{
    class container;
}

namespace tct::properties
{
    class properties;

	/**
	 * Built-in archiver for (de)serializing to/from GPDS (https://github.com/simulton/gpds).
	 */
    class archiver_gpds
    {
    public:
		/**
		 * Serialize properties to GPDS container.
		 *
		 * @param p The properties to serialize.
		 * @return The serialized container.
		 */
        [[nodiscard]]
		gpds::container
		save(const properties& p) const;

		/**
		 * Deserialize properties from a GPDS container.
		 *
		 * @param p The properties to deserialize into.
		 * @param c The container to deserialize.
		 * @return @p true on success, @p false otherwise with an optional error message.
		 */
        std::pair<bool, std::string>
		load(properties&p, const gpds::container& c) const;

    private:
        static
        void
        write_recursively(gpds::container& root, const ::tct::properties::properties& p);

        static
        void
        read_recursively(const gpds::container& root, ::tct::properties::properties& p);
    };
}
